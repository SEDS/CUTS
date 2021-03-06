// -*- C++ -*-

//=============================================================================
/**
 * @file      performance_i.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_PERFORMANCE_I_H_
#define _CUTS_PERFORMANCE_I_H_

#include "Benchmark_Agent.h"
#include "Component_Metric.h"
#include "idl/performanceC.h"

void CUTS_Export
operator >>= (const CUTS::Component_Metric & src, CUTS_Component_Metric & dst);

void CUTS_Export
operator <<= (CUTS::Component_Metric & cm, CUTS_Benchmark_Agent & agent);

#if defined (__CUTS_INLINE__)
#include "cuts/performance_i.inl"
#endif

#endif  // !defined _CUTS_PERFORMANCE_I_H_
