// $Id$

#include "UDM_Utility_T.h"
#include "BE_algorithm.h"
#include "modelgen.h"

// BOOST headers
#include "boost/bind.hpp"

// UDM headers
#include "Uml.h"

// STL headers
#include <algorithm>
#include <sstream>

/**
 * Functor used for sorting the branch transition. The sorting of
 * the branches is based on the position of its connecting action.
 * The actions are sorted from top to bottom, which corresponds to
 * the ordering of the statements. The bottom most action is the
 * only one that can have a branch transition with an empty condition.
 */
struct CUTS_BE_BranchTransition_Sort
{
  struct Position
  {
    /// X-value of the position.
    long x;

    /// Y-value of the position
    long y;

    /**
     * Extraction operator. This method takes a string and extracts
     * the coordinates from it. The format of the string should be
     * (x, y). If the source string does not have coordinates stored
     * in this format, it will cause unpredictable behavior.
     *
     * @param[in]     str     Source string with the x-,y-coordinates
     */
    void operator <<= (const std::string & str)
    {
      char tmp;

      std::istringstream istr (str);

      istr >> tmp;
      istr >> this->x;
      istr >> tmp;
      istr >> this->y;
    }
  };

  /**
   * Functor operation. This method will determine which object
   * is above the other object.
   */
  bool operator () (const CHAOS::BranchTransition & lhs,
                    const CHAOS::BranchTransition & rhs)
  {
    CHAOS::ActionBase lhs_action (lhs.dstBranchTransition_end ());
    CHAOS::ActionBase rhs_action (rhs.dstBranchTransition_end ());

    Position lhs_pos;
    lhs_pos <<= lhs_action.position ();

    Position rhs_pos;
    rhs_pos <<= rhs_action.position ();

    return lhs_pos.y < rhs_pos.y;
  }
};

//
// CUTS_BE_Execution_Visitor_T
//
template <typename CONTEXT>
CUTS_BE_Execution_Visitor_T <CONTEXT>::
CUTS_BE_Execution_Visitor_T (CONTEXT & context)
: context_ (context),
  ignore_effects_ (false),
  depth_ (0)
{

}

//
// ~CUTS_BE_Execution_Visitor_T
//
template <typename CONTEXT>
CUTS_BE_Execution_Visitor_T <CONTEXT>::
~CUTS_BE_Execution_Visitor_T (void)
{

}

//
// generate
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
generate (const CHAOS::SingleInputBase & base)
{
  CHAOS::Input input = base.dstInput ();

  if (input != Udm::null)
  {
    CUTS_BE::visit <CONTEXT> (input,
      [&] (CHAOS::Input item) {item.Accept (*this);});
  }
}


//
// generate
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
generate (const CHAOS::MultiInputBase & base)
{
  typedef std::set <CHAOS::MultiInput> MultiInput_Set;
  MultiInput_Set inputs = base.dstMultiInput ();

  if (!inputs.empty ())
  {
    CUTS_BE::visit <CONTEXT> (inputs,
      [&] (MultiInput_Set::value_type item) {item.Accept (*this);});
  }
}

//
// Visit_Input
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
Visit_Input (const CHAOS::Input & input)
{
  CHAOS::InputAction action =
    CHAOS::InputAction::Cast (input.dstInput_end ());

  CUTS_BE::visit <CONTEXT> (action,
    [&] (CHAOS::InputAction item) {item.Accept (*this);});
}


//
// Visit_MultiInput
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
Visit_MultiInput (const CHAOS::MultiInput & input)
{
  CHAOS::MultiInputAction action = input.dstMultiInput_end ();

  CUTS_BE::visit <CONTEXT> (action,
    [&] (CHAOS::MultiInputAction item) {item.Accept (*this);});
}

//
// Visit_InputAction
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
Visit_InputAction (const CHAOS::InputAction & action)
{
  // Add the <action> to the top of the stack.
  this->action_stack_.push (action);

  // Visit the effect.
  CHAOS::InputEffect input_effect = action.dstInputEffect ();

  if (input_effect != Udm::null)
  {
    CUTS_BE::visit <CONTEXT> (input_effect,
      [&] (CHAOS::InputEffect item) {item.Accept (*this);});
  }

  // Remove the <action> from the stack since we have
  // completed its behavior.
  this->action_stack_.pop ();
}

//
// Visit_MultiInputAction
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
Visit_MultiInputAction (const CHAOS::MultiInputAction & action)
{
  // Add the <action> to the top of the stack.
  this->action_stack_.push (action);

  // Visit the effect.
  CHAOS::InputEffect input_effect = action.dstInputEffect ();

  if (input_effect != Udm::null)
  {
    CUTS_BE::visit <CONTEXT> (input_effect,
      [&] (CHAOS::InputEffect item) {item.Accept (*this);});
  }

  // Remove the <action> from the stack since we have
  // completed its behavior.
  this->action_stack_.pop ();
}

//
// Visit_InputEffect
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
Visit_InputEffect (const CHAOS::InputEffect & effect)
{
  // Write the postcondition for this <effect>.
  std::string postcondition = effect.Postcondition ();

  if (!postcondition.empty ())
  {
    CUTS_BE_Postcondition_T <CONTEXT> postcondition_gen (this->context_);
    postcondition_gen.generate (postcondition);
  }

  // Visit the next state in the chain.
  this->Visit_StateBase (effect.dstInputEffect_end ());
}

//
// Visit_Effect
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
Visit_Effect (const CHAOS::Effect & effect)
{
  // Write the postcondition for this <effect>.
  std::string postcondition = effect.Postcondition ();

  if (!postcondition.empty ())
  {
    CUTS_BE_Postcondition_T <CONTEXT> postcondition_gen (this->context_);
    postcondition_gen.generate (postcondition);
  }

  // Visit the next state in the chain.
  this->Visit_StateBase (effect.dstEffect_end ());
}

//
// Visit_StateBase
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
Visit_StateBase (const CHAOS::StateBase & base)
{
  // Get the typename of the state.
  Uml::Class type_name = base.type ();

  if (type_name == CHAOS::State::meta)
  {
    CHAOS::State state = CHAOS::State::Cast (base);

    CUTS_BE::visit <CONTEXT> (state,
      [&] (CHAOS::State item) {item.Accept (*this);});
  }
  else if (type_name == CHAOS::BranchState::meta)
  {
    CHAOS::BranchState branch = CHAOS::BranchState::Cast (base);

    CUTS_BE::visit <CONTEXT> (branch,
      [&] (CHAOS::BranchState item) {item.Accept (*this);});
  }
  else if (type_name == CHAOS::DoWhileState::meta)
  {
    CHAOS::DoWhileState do_while (CHAOS::DoWhileState::Cast (base));

    CUTS_BE::visit <CONTEXT> (do_while,
      [&] (CHAOS::DoWhileState item) {item.Accept (*this);});
  }
  else if (type_name == CHAOS::WhileState::meta)
  {
    CHAOS::WhileState while_state (CHAOS::WhileState::Cast (base));

    CUTS_BE::visit <CONTEXT> (while_state,
      [&] (CHAOS::WhileState item) {item.Accept (*this);});
  }
}

//
// Visit_DoWhileState
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
Visit_DoWhileState (const CHAOS::DoWhileState & do_while)
{
  // Generate the implemenation for the do...while control block.
  CUTS_BE_Do_While_Begin_T <CONTEXT> do_while_begin (this->context_);
  do_while_begin.generate ();

  this->Visit_LoopState (do_while);

  CUTS_BE_Do_While_End_T <CONTEXT> do_while_end (this->context_);
  do_while_end.generate ();

  // We are starting to generate the do...while condition.
  CUTS_BE_Do_While_Condition_Begin_T <CONTEXT> do_while_condition_begin (this->context_);
  do_while_condition_begin.generate ();

  CUTS_BE_Precondition_T <CONTEXT> precondition_gen (this->context_);
  precondition_gen.generate (do_while.LoopingCondition ());

  // We are done generating the do...while condition.
  CUTS_BE_Do_While_Condition_End_T <CONTEXT> do_while_condition_end (this->context_);
  do_while_condition_end.generate ();

  // Goto the terminal for this control block.
  this->goto_to_terminal ();
}

//
// Visit_WhileState
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
Visit_WhileState (const CHAOS::WhileState & while_state)
{
  // We are starting to generate the do...while condition.
  CUTS_BE_While_Condition_Begin_T <CONTEXT> while_condition_begin (this->context_);
  while_condition_begin.generate ();

  CUTS_BE_Precondition_T <CONTEXT> precondition_gen (this->context_);
  precondition_gen.generate (while_state.LoopingCondition ());

  // We are done generating the do...while condition.
  CUTS_BE_While_Condition_End_T <CONTEXT> while_condition_end (this->context_);
  while_condition_end.generate ();

  // Generate the implemenation for the do...while control
  // block.
  CUTS_BE_While_Begin_T <CONTEXT> while_begin_gen (this->context_);
  while_begin_gen.generate ();

  this->Visit_LoopState (while_state);

  CUTS_BE_While_End_T <CONTEXT> while_end_gen (this->context_);
  while_end_gen.generate ();

  // Goto the terminal for this control block.
  this->goto_to_terminal ();
}

//
// goto_to_terminal
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
goto_to_terminal (void)
{
  // Since we have finished the branching, we can continue generating
  // the remainder of the behavior that occurs after the branching.
  if (!this->terminal_state_.empty ())
  {
    CHAOS::Terminal terminal = this->terminal_state_.top ();
    this->terminal_state_.pop ();

    terminal.Accept (*this);
  }
}

//
// Visit_LoopTransition
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
Visit_LoopTransition (const CHAOS::LoopTransition & transition)
{
  CHAOS::ActionBase action (transition.dstLoopTransition_end ());
  this->Visit_ActionBase (action);
}

//
// Visit_LoopState
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
Visit_LoopState (const CHAOS::LoopState & loop_state)
{
  CHAOS::LoopTransition loop_transition (loop_state.dstLoopTransition ());
  loop_transition.Accept (*this);
}

//
// Visit_State
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
Visit_State (const CHAOS::State & state)
{
  // Generate information about the state.
  CUTS_BE_State_T <CONTEXT> state_gen (this->context_);
  state_gen.generate (state);

  // Check to see if this state has any finish connections. If it
  // does, then we need to see if any of the finish connections is
  // for the current input action.
  typedef std::set <CHAOS::Finish> Finish_Set;
  Finish_Set finish_set = state.dstFinish ();

  CHAOS::Finish finish;

  if (Udm::contains (boost::bind (std::equal_to <CHAOS::BehaviorInputAction> (),
      this->action_stack_.top (),
      boost::bind (&CHAOS::Finish::dstFinish_end,
                    _1))) (finish_set, finish))
  {
    return;
  }

  // Visit the transition that connected to this state.
  CHAOS::Transition transition = state.dstTransition ();

  if (transition != Udm::null)
  {
    CUTS_BE::visit <CONTEXT> (transition,
      [&] (CHAOS::Transition item) {item.Accept (*this);});
  }
  else
  {
    // Ok, so we are at a terminal transition.
    CHAOS::TerminalTransition term = state.dstTerminalTransition ();

    CUTS_BE::visit <CONTEXT> (term,
      [&] (CHAOS::TerminalTransition item) {item.Accept (*this);});
  }
}

//
// Visit_BranchState
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
Visit_BranchState (const CHAOS::BranchState & state)
{
  // We use the greater than comparison so that empty string,
  typedef std::set <CHAOS::BranchTransition,
                    CUTS_BE_BranchTransition_Sort> Transition_Set;

  Transition_Set transitions =
    state.dstBranchTransition_sorted (Transition_Set::key_compare ());

  // Signal the backend we are starting a branch state.
  CUTS_BE_Branches_Begin_T <CONTEXT> branches_begin_gen (this->context_);
  branches_begin_gen.generate (transitions.size ());

  CUTS_BE::visit <CONTEXT> (transitions,
    [&] (CHAOS::BranchTransition item) {item.Accept (*this);});

  // Signal the backend we are starting a branch state.
  CUTS_BE_Branches_End_T <CONTEXT> branches_end_gen (this->context_);
  branches_end_gen.generate ();

  // Since we have finished the branching, we can continue generating
  // the remainder of the behavior that occurs after the branching.
  this->goto_to_terminal ();
}

//
// Visit_TerminalTransition
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
Visit_TerminalTransition (const CHAOS::TerminalTransition & transition)
{
  CHAOS::Terminal terminal = transition.dstTerminalTransition_end ();

  if (this->terminal_state_.empty () ||
      this->terminal_state_.top () != terminal)
  {
    this->terminal_state_.push (terminal);
  }
}

//
// Visit_Terminal
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
Visit_Terminal (const CHAOS::Terminal & terminal)
{
  CHAOS::TerminalEffect effect = terminal.dstTerminalEffect ();
  effect.Accept (*this);
}

//
// Visit_TerminalEffect
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
Visit_TerminalEffect (const CHAOS::TerminalEffect & effect)
{
  CHAOS::StateBase state = effect.dstTerminalEffect_end ();
  this->Visit_StateBase (state);
}

//
// Visit_Transition
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
Visit_Transition (const CHAOS::Transition & transition)
{
  CHAOS::ActionBase action = transition.dstTransition_end ();
  this->Visit_ActionBase (action);
}

//
// Visit_BranchTransition
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
Visit_BranchTransition (const CHAOS::BranchTransition & transition)
{
  std::string condition = transition.Condition ();

  if (!condition.empty ())
  {
    // We first need to write the condition for the branch before
    // we can start writing the actual branch statements.
    CUTS_BE_Branch_Condition_Begin_T <CONTEXT> branch_condition_begin (this->context_);
    branch_condition_begin.generate ();

    CUTS_BE_Precondition_T <CONTEXT> precondition_gen (this->context_);
    precondition_gen.generate (condition);

    CUTS_BE_Branch_Condition_End_T <CONTEXT> branch_condition_end (this->context_);
    branch_condition_end.generate ();
  }
  else
  {
    // This is an *else* branch. There should only be one of these
    // and it should be the last one in the listing.
    CUTS_BE_Branch_No_Condition_T <CONTEXT> branch_no_condition (this->context_);
    branch_no_condition.generate ();
  }

  // We are now ready to write the branch statements.
  CUTS_BE_Branch_Begin_T <CONTEXT> branch_begin_gen (this->context_);
  branch_begin_gen.generate ();

  CHAOS::ActionBase action = transition.dstBranchTransition_end ();
  this->Visit_ActionBase (action);

  CUTS_BE_Branch_End_T <CONTEXT> branch_end_gen (this->context_);
  branch_end_gen.generate ();
}

//
// Visit_ActionBase
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
Visit_ActionBase (const CHAOS::ActionBase & action_base)
{
  Uml::Class type = action_base.type ();

  // We are placing the order of the action types in fast path
  // order. We know there will be far more <Action> elements
  // than any type.
  if (type == CHAOS::Action::meta)
  {
    CHAOS::Action::Cast (action_base).Accept (*this);
  }
  else if (type == CHAOS::OutputAction::meta)
  {
    CHAOS::OutputAction::Cast (action_base).Accept (*this);
  }

  // Continue down the chain.
  CHAOS::Effect effect = action_base.dstEffect ();
  effect.Accept (*this);
}

//
// Visit_Property
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
Visit_Property (const CHAOS::Property & property)
{
  CUTS_BE_Action_Property_T <CONTEXT> action_property_gen (this->context_);
  action_property_gen.generate (property);
}

//
// Visit_Action
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
Visit_Action (const CHAOS::Action & action)
{
  // Get action type and it's worker parent. This will help all
  // the generators since they will not have to do this themselves.
  CHAOS::Action action_type = action;

  while (CHAOS::Action (action_type.Archetype ()) != Udm::null)
    action_type = action_type.Archetype ();

  // Let's tell the <traits_> to begin generating an action.
  CHAOS::Worker worker = action_type.Worker_parent ();
  CUTS_BE_WorkerAction_Begin_T <CONTEXT> worker_action_begin (this->context_);
  worker_action_begin.generate (worker, action);

  // Generate the parameters for the action.
  typedef std::set <CHAOS::Property,
                    Sort_By_Position <CHAOS::Property> > Property_Set;

  Property_Set properties =
    action.Property_kind_children_sorted (Sort_By_Position <CHAOS::Property> ());

  if (!properties.empty ())
  {
    CUTS_BE_Action_Properties_Begin_T <CONTEXT> action_props_begin_gen (this->context_);
    action_props_begin_gen.generate (properties.size ());

    CUTS_BE::visit <CONTEXT> (properties,
      [&] (Property_Set::value_type item) {item.Accept (*this);});

    CUTS_BE_Action_Properties_End_T <CONTEXT> action_props_end_gen (this->context_);
    action_props_end_gen.generate ();
  }

  // Let's tell the <traits_> to end generating an action.
  CUTS_BE_Action_End_T <CONTEXT> action_end (this->context_);
  action_end.generate ();
}

//
// Visit_OutputAction
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
Visit_OutputAction (const CHAOS::OutputAction & action)
{
  CUTS_BE_OutputAction_Begin_T <CONTEXT> output_action_begin (this->context_);
  output_action_begin.generate (action);

  typedef std::vector <CHAOS::Property> Property_Set;
  Property_Set properties = action.Property_kind_children ();

  CUTS_BE::visit <CONTEXT> (properties,
    [&] (CHAOS::Property item) {this->Visit_OutputAction_Property (item);});

  CUTS_BE_OutputAction_End_T <CONTEXT> output_action_end (this->context_);
  output_action_end.generate (action);
}

////
//// Visit_CompositeAction
////
//template <typename CONTEXT>
//void CUTS_BE_Execution_Visitor_T <CONTEXT>::
//Visit_CompositeAction (const CHAOS::CompositeAction & action)
//{
//  typedef std::vector <CHAOS::InputAction> InputAction_Set;
//  InputAction_Set actions = action.InputAction_children ();
//
//  if (!actions.empty ())
//  {
//    // Composite actions are only allowed to have a single input
//    // action. Therefore, we only visit the first action in the set.
//    CUTS_BE::visit <CONTEXT> (CHAOS::InputAction::Cast (actions.front ()),
//      boost::bind (&CHAOS::InputAction::Accept, _1, boost::ref (*this)));
//  }
//}

//
// Visit_OutputAction_Property
//
template <typename CONTEXT>
void CUTS_BE_Execution_Visitor_T <CONTEXT>::
Visit_OutputAction_Property (const CHAOS::Property & property)
{
  CHAOS::OutputAction parent =
    CHAOS::OutputAction::Cast (property.parent ());

  CUTS_BE_OutputAction_Property_T <CONTEXT> output_action_property (this->context_);
  output_action_property.generate (parent, property);
}
