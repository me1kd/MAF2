/*=========================================================================
Program:   Multimod Application Framework
Module:    $RCSfile: mafStringTest.h,v $
Language:  C++
Date:      $Date: 2007-11-05 15:11:34 $
Version:   $Revision: 1.4 $
Authors:   Marco Petrone, Stefano Perticoni
==========================================================================
Copyright (c) 2002/2004 
CINECA - Interuniversity Consortium (www.cineca.it)
=========================================================================*/

#ifndef __CPP_UNIT_MAFSTRINGTEST_H__
#define __CPP_UNIT_MAFSTRINGTEST_H__

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>



class mafStringTest : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE( mafStringTest );
  CPPUNIT_TEST( Test );
  CPPUNIT_TEST_SUITE_END();

  protected:
    /** Test multiple string features with a single test */
    void Test();
};


int
main( int argc, char* argv[] )
{
  // Create the event manager and test controller
  CPPUNIT_NS::TestResult controller;

  // Add a listener that colllects test result
  CPPUNIT_NS::TestResultCollector result;
  controller.addListener( &result );        

  // Add a listener that print dots as test run.
  CPPUNIT_NS::BriefTestProgressListener progress;
  controller.addListener( &progress );      

  // Add the top suite to the test runner
  CPPUNIT_NS::TestRunner runner;
  runner.addTest( mafStringTest::suite());
  runner.run( controller );

  // Print test in a compiler compatible format.
  CPPUNIT_NS::CompilerOutputter outputter( &result, CPPUNIT_NS::stdCOut() );
  outputter.write(); 

  return result.wasSuccessful() ? 0 : 1;
}

#endif