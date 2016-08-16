/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.28                          *
*        Compiled Jan 30 2015, 16:41:06                              *
*        (c) 2015 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
// USER END

#include "DIALOG.h"
#include "manager.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

static GRAPH_DATA_Handle  _ahData; // Array of handles for the GRAPH_DATA objects
static GRAPH_DATA_Handle  _ahData1;
static GRAPH_SCALE_Handle _hScaleV;   // Handle of vertical scale
static GRAPH_SCALE_Handle _hScaleH;   // Handle of horizontal scale
static I16 _aValue[30];
static int _Stop = 0;

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] =
{
  { FRAMEWIN_CreateIndirect, "Manager", ID_FRAMEWIN_1, 0, 60, 320, 180, 0, 0x0, 0 },
  { GRAPH_CreateIndirect, "Graph", ID_GRAPH_0, 18, 18, 272, 50, 0, 0x0, 0 },
  { GRAPH_CreateIndirect, "Graph", ID_GRAPH_1, 18, 77, 272, 50, 0, 0x0, 0 },
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)
// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  WM_HWIN hItem1;
  WM_HWIN  hDlg;
  hDlg = pMsg->hWin;

  switch (pMsg->MsgId)
  {
	  case WM_INIT_DIALOG:
	  {
	//    hItem1 = pMsg->hWin;
		FRAMEWIN_SetTitleVis(pMsg->hWin, 0);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_GRAPH_0);
		hItem1 = WM_GetDialogItem(pMsg->hWin, ID_GRAPH_1);

		GRAPH_SetGridDistY(hItem, 10);
		GRAPH_SetGridDistY(hItem1, 10);
		GRAPH_SetGridVis(hItem, 1);
		GRAPH_SetGridVis(hItem1, 1);
		GRAPH_SetGridFixedX(hItem, 1);
		GRAPH_SetGridFixedX(hItem1, 1);

		_hScaleV = GRAPH_SCALE_Create( 5, GUI_TA_RIGHT, GRAPH_SCALE_CF_VERTICAL, 100);
		GRAPH_SCALE_SetTextColor(_hScaleV, GUI_GREEN);
		GRAPH_AttachScale(hItem, _hScaleV);
		GRAPH_AttachScale(hItem1, _hScaleV);
		//
		// Create and add horizontal scale
		//
		_hScaleH = GRAPH_SCALE_Create(5, GUI_TA_CENTER, GRAPH_SCALE_CF_HORIZONTAL, 50);
		GRAPH_SCALE_SetTextColor(_hScaleH, GUI_BLUE);
		GRAPH_AttachScale(hItem, _hScaleH);
		GRAPH_AttachScale(hItem1, _hScaleH);

		  _ahData = GRAPH_DATA_YT_Create(GUI_BLUE, 500 , mem, 100);
		   GRAPH_AttachData(hItem, _ahData);

		break;
	  }
	  default:
	  {
		  WM_DefaultProc(pMsg);
		  break;
	  }
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateManager
*/

WM_HWIN CreateManager(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWin;
}


void Manager(void *pvParameters)
{

	WM_HWIN hWin=CreateManager();
	WM_HWIN hGraph,hGraph1;

	hGraph=WM_GetDialogItem(hWin, ID_GRAPH_0);
	hGraph1=WM_GetDialogItem(hWin, ID_GRAPH_1);
//	for (int i = 0; i<10; i++)
//	{
//	  _aValue[i] = get_random(0,40);
//	}
	  _ahData = GRAPH_DATA_YT_Create(GUI_BLUE, 500 , 0, 0);
	  _ahData1 = GRAPH_DATA_YT_Create(GUI_GREEN, 500 , 0, 0);
	   GRAPH_AttachData(hGraph, _ahData);
	   GRAPH_AttachData(hGraph1, _ahData1);

	   vTaskDelete(Menu_Handle);

	while(1)
	{
		vTaskDelay(1000);
		for (int i = 0; i<10; i++)
		{
		  _aValue[i] = get_random(0,100);
		}
		GRAPH_DATA_YT_AddValue(_ahData, _aValue[0]);
		GRAPH_DATA_YT_AddValue(_ahData1, _aValue[2]);
//		GUI_Exec();
//		 GUI_SetFont(&GUI_Font24_ASCII);
//		 GUI_SetColor(GUI_BLACK);
//		 GUI_SetTextMode(GUI_TM_TRANS);
//		GUI_DispDecAt(xPortGetFreeHeapSize(),160,230,5);
	}

}
