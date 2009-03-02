// $Id$

#include "Response_Time_Evaluator.h"

#if !defined (__CUTS_INLINE__)
#include "Response_Time_Evaluator.inl"
#endif

#include "Component_Assembly.h"
#include "Component_Instance.h"
#include "Deployment.h"
#include "Host.h"
#include "boost/bind.hpp"

//
// evaluate
//
void CUTS_Response_Time_Evaluator::
evaluate (const CUTS_Component_Assembly & assembly,
          const CUTS_Deployment & deployment,
          result_type & results)
{
  this->assembly_ = &assembly;
  this->results_ = & results;

  // Iterate over each host in the deployment.
  CUTS_Deployment::map_type::CONST_ITERATOR host_iter (deployment.items ());

  CUTS_Host * host;
  CUTS_Component_Instance * inst;

  for (; !host_iter.done (); ++ host_iter)
  {
    // Get the utilization of the host.
    host = host_iter->item ();
    this->host_util_ = host->utilization ();

    // Iterate over each component on the current host.
    CUTS_Host::container_type::CONST_ITERATOR inst_iter (host->instances ());

    for ( ; !inst_iter.done (); ++ inst_iter)
    {
      inst = *inst_iter;
      // inst->response_time (util);

      std::for_each (inst->ports ().begin (),
                     inst->ports ().end (),
                     boost::bind (&CUTS_Response_Time_Evaluator::evaluate_i,
                                  this,
                                  _1));
    }
  }
}

//
// evaluate_i
//
void CUTS_Response_Time_Evaluator::
evaluate_i (CUTS_Behavior_Graph::vertex_descriptor port)
{
  // Get the port details.
  CUTS_Port_Details details;
  this->assembly_->get_port_details (port, details);

  if (details.input_)
  {
    // Elongate the ports service time.
    double baseline_util =
      details.arrival_rate_ * details.service_time_ / 1000.0;
    double used_util = this->host_util_ - baseline_util;

    double elongated = details.service_time_ / (1 - used_util);
    double rt = 1.0 / (1.0 / elongated - details.arrival_rate_ / 1000.0);

    // Save the results.
    this->results_->bind (details.name_, rt);
  }
}