/*=========================================================================
  Program:   Multimod Application Framework
  Module:    $RCSfile: mafOpCreateSlicer.cpp,v $
  Language:  C++
  Date:      $Date: 2008-03-06 11:55:06 $
  Version:   $Revision: 1.1 $
  Authors:   Paolo Quadrani
==========================================================================
  Copyright (c) 2001/2005 
  CINECA - Interuniversity Consortium (www.cineca.it)
=========================================================================*/

#include "mafDefines.h" 
//----------------------------------------------------------------------------
// NOTE: Every CPP file in the MAF must include "mafDefines.h" as first.
// This force to include Window,wxWidgets and VTK exactly in this order.
// Failing in doing this will result in a run-time error saying:
// "Failure#0: The value of ESP was not properly saved across a function call"
//----------------------------------------------------------------------------


#include "mafOpCreateSlicer.h"
#include "mafDecl.h"
#include "mafEvent.h"

#include "mafVMESlicer.h"

//----------------------------------------------------------------------------
// Constants :
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
mafCxxTypeMacro(mafOpCreateSlicer);
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
mafOpCreateSlicer::mafOpCreateSlicer(const wxString &label) :
mafOp(label)
//----------------------------------------------------------------------------
{
  m_OpType	= OPTYPE_OP;
  m_Canundo = true;
  
  m_Slicer    = NULL;
  m_SlicedVME = NULL;
}
//----------------------------------------------------------------------------
mafOpCreateSlicer::~mafOpCreateSlicer()
//----------------------------------------------------------------------------
{
  mafDEL(m_Slicer);
}
//----------------------------------------------------------------------------
mafOp* mafOpCreateSlicer::Copy()   
//----------------------------------------------------------------------------
{
	return new mafOpCreateSlicer(m_Label);
}
//----------------------------------------------------------------------------
bool mafOpCreateSlicer::Accept(mafNode *node)
//----------------------------------------------------------------------------
{
  return (node != NULL);
}
//----------------------------------------------------------------------------
void mafOpCreateSlicer::OpRun()
//----------------------------------------------------------------------------
{
  mafString title = _("Choose VME to slice");
  mafEvent *e; e = new mafEvent();
  e->SetId(VME_CHOOSE);
  e->SetArg((long)&mafOpCreateSlicer::VolumeAccept);
  e->SetString(&title);
  mafEventMacro(*e);

  int result = OP_RUN_CANCEL;

  mafNode *n = e->GetVme();
  if (n != NULL)
  {
		mafNEW(m_Slicer);
		m_Slicer->SetName("slicer");
		m_Output = m_Slicer;

    m_SlicedVME = n;
    m_Slicer->SetSlicedVMELink(m_SlicedVME);
    result = OP_RUN_OK;
  }
  mafEventMacro(mafEvent(this, result));
}
//----------------------------------------------------------------------------
void mafOpCreateSlicer::OpDo()
//----------------------------------------------------------------------------
{
  double center[3] = {0.0,0.0,0.0}, rot[3] = {0.0,0.0,0.0};
  mafOBB b;
  m_Slicer->ReparentTo(mafVME::SafeDownCast(m_Input));
  rot[0] = rot[1] = rot[2] = 0;
  ((mafVME *)m_SlicedVME)->GetOutput()->GetVMELocalBounds(b);
  if (b.IsValid())
  {
    b.GetCenter(center);
  }
  m_Slicer->SetPose(center,rot,0);
}