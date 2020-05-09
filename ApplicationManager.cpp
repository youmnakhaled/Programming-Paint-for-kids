#include "ApplicationManager.h"
#include "Actions\AddRectAction.h"
#include "Actions\AddLineAction.h"
#include "Actions\AddTriAction.h"
#include "Actions\AddEllipseAction.h"
#include "Actions\AddRhombusAction.h"
#include "Actions\Select.h"
#include"Actions\CutAction.h"
#include"Actions\CopyAction.h"
#include"Actions\PasteAction.h"
#include"Actions\DeleteAction.h"
#include "Actions\ChangeFillColorAction.h"
#include"Actions\ChangeDrawColorAction.h"
#include"Actions\switchtodrawmode.h"
#include"Actions\switchtoplaymode.h"
#include"Actions\pickbycolor.h"
#include"Actions\pickbyshape.h"
#include"Actions\Exit.h"
#include"Actions\SaveAction.h"
#include"Figures/CLINE.h"
#include"Figures/CRhombus.h"
#include"Figures/CEllipse.h"
#include"Figures/CTri.h"
#include"Figures/CRectangle.h"
#include"Figures/CFigure.h"

ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	
	FigCount = 0;
		
	//Create an array of figure pointers and set them to NULL		
	for(int i=0; i<MaxFigCount; i++)
		FigList[i] = NULL;
	SelectedFig=NULL;
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction();		
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;
	
	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
		case DRAW_RECT:
			pAct = new AddRectAction(this);
			break;

		case DRAW_LINE:
			pAct = new AddLineAction(this);
			break;

		case DRAW_TRI:
			pAct = new AddTriAction(this);
			break;

		case DRAW_RHOMBUS:
			pAct = new AddRhombusAction(this);
			break;

		case DRAW_ELLIPSE:
			pAct = new AddEllipseAction(this);
			break;

		case SELECT:
			pAct=new Select(this);
			break;

		case CHNG_DRAW_CLR:
			pAct = new ChangeDrawColorAction(this);
			break;

		case CHNG_FILL_CLR:
			pAct = new ChangeFillColorAction(this);
			break;

		case TO_PLAY:
			pAct = new switchtoplaymode(this);
			break;

		case TO_DRAW:
			pAct = new switchtodrawmode(this);
			break;

		case PICK_COLOR:
			pAct = new pickbycolor(this);
			break;

		case PICK_SHAPE:
			pAct = new pickbyshape(this);
			break;


		case EXIT:
			pAct = new Exit(this);
			break;
			
		case CUT_SHAPE:
			pAct= new CutAction(this);
			break;

		case COPY_SHAPE:
			pAct= new CopyAction(this);
			break;

		case PASTE_SHAPE:
			pAct=new PasteAction(this);
			break;

		case DEL:
			pAct=new DeleteAction(this);
			break;

		case SAVE:
			pAct = new savegraph(this);
			break;
		
		case STATUS:	//a click on the status bar ==> no action
			return;
	}
	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
		pAct = NULL;
	}
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if(FigCount < MaxFigCount )
		FigList[FigCount++] = pFig;	
}
////////////////////////////////////////////////////////////////////////////////////
//checks for figures
bool ApplicationManager::check(CFigure*f)
{
	int count = 0;
	for (int i = 0; i < FigCount; i++)
	{
		if (f == FigList[i])
		{
			count++;
		}
	}
		if (count > 0)
			return true;
		else
			return false;
	
}
void ApplicationManager:: SaveAll(ofstream &OutFile)
{

	OutFile << pOut->CrntDrawColor() << "\t" << pOut->CrntFillColor() <<  endl;
	OutFile << FigCount << endl;
	for (int i = 0; i < FigCount; i++)
	{

		OutFile << FigList[i]->getID() <<endl;
		FigList[i]->Save(OutFile);
	}

}
//gets random figure
int ApplicationManager::randomfigure(int &count)
{
	int number = 0;
	number = rand() % (FigCount - 1) + 1;
	CRectangle*F = dynamic_cast<CRectangle*>(FigList[number]);
	CTri*T = dynamic_cast<CTri*>(FigList[number]);
	CCEllipse*E = dynamic_cast<CCEllipse*>(FigList[number]);
	CRhombus*R = dynamic_cast<CRhombus*>(FigList[number]);
	CLINE*L = dynamic_cast<CLINE*>(FigList[number]);
	if (F != NULL)
	{
		pOut->PrintMessage("pick rectangles:");
		for (int i = 0; i < FigCount; i++)
		{
			F = NULL;
			if (F = dynamic_cast<CRectangle*>(FigList[i]))
				count++;
		}
		return 1;
	}
	else if (L != NULL)
	{
		pOut->PrintMessage("pick lines:");
		for (int i = 0; i < FigCount; i++)
		{
			L = NULL;
			if (L = dynamic_cast<CLINE*>(FigList[i]))
				count++;
		}
		return 2;
	}
	else if (R != NULL)
	{
		pOut->PrintMessage("pick rhombus:");
		for (int i = 0; i < FigCount; i++)
		{
			R = NULL;
			if (R = dynamic_cast<CRhombus*>(FigList[i]))
				count++;
		}
		return 3;
	}
	else if (E != NULL)
	{
		pOut->PrintMessage("pick ellipse:");
		for (int i = 0; i < FigCount; i++)
		{
			E = NULL;
			if (E = dynamic_cast<CCEllipse*>(FigList[i]))
				count++;
		}
		return 4;
	}
	else if (T != NULL)
	{
		pOut->PrintMessage("pick triangles:");
		for (int i = 0; i < FigCount; i++)
		{
			T = NULL;
			if (T = dynamic_cast<CTri*>(FigList[i]))
				count++;
		}
		return 5;
	}

}
//gets random color
color ApplicationManager::randomcolor(int & count)
{
	int number = 0;
	number = rand() % (FigCount - 1) + 1;
	color clr = FigList[number]->getcolor();
	if (clr == RED)
		pOut->PrintMessage("pick red figure");
	else if (clr == BLUE)
		pOut->PrintMessage("pick blue figure");
	else if (clr == GREEN)
		pOut->PrintMessage("pick green figure");
	else if (clr == BLACK)
		pOut->PrintMessage("pick black figure");
	else if (clr == WHITE)
		pOut->PrintMessage("pick white figure");
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->getcolor() == FigList[number]->getcolor())
			count++;
	}
	return FigList[number]->getcolor();
}
//deletes figure
void ApplicationManager::disappear(CFigure*f)
{
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i] == f)
		{
			delete FigList[i];
			FigList[i] = FigList[FigCount - 1];
			FigCount--;
			break;
		}
	}
	pOut->ClearDrawArea();
}
CFigure *ApplicationManager::GetSelectedFig()
{
	return SelectedFig;
}

void ApplicationManager:: SetSelectedFigure(CFigure* c )
{
	SelectedFig=c;
}
void ApplicationManager:: Setclipboard(CFigure* Figure)
{
	Clipboard=Figure;
}
CFigure * ApplicationManager::Getclipboard() const
{
	return Clipboard;
}
void ApplicationManager::TranslateShape(CFigure *fig,Point P1)
{
	fig->TRANSLATE(P1);
}	
CFigure *ApplicationManager::GetFigure(int X, int Y) const
{
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL
	Point P1;
	P1.x=X; P1.y=Y;
	for (int i=FigCount-1; i>=0 ; i--)
	{
		bool c=FigList[i]->isinside(P1);
		if (c)
			return FigList[i];
		
	}
	return NULL;


	//Add your code here to search for a figure given a point x,y	
	//Remember that ApplicationManager only calls functions do NOT implement it.
}

void ApplicationManager :: Deletefigure(CFigure* d)
{
	for(int i=0; i<FigCount; i++)
			{
		if ( FigList[i] == d ) 
			{		
	
				delete FigList[i];
			FigList[i] = FigList[FigCount - 1];
			FigCount--;
			break;
		}
	}
}

//void  ApplicationManager:: UpdateOrderOfArray ()
//{ 
//	for(int i=0; i<FigCount; i++)
//{
//	if ( FigList[i] == NULL ) 
//	{
//		for (int j=i ; j<FigCount-1 ; j++)
//		{
//			FigList[i]=FigList[i+1];
//		}
//	}
//}
//	FigList[FigCount]=NULL;
//	FigCount--;
//}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{	
	pOut->ClearDrawArea();
	for(int i=0; i<FigCount; i++)
		FigList[i]->Draw(pOut);		//Call Draw function (virtual member fn)
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{	return pIn; }
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{	return pOut; }
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<FigCount; i++)
	{

		delete FigList[i];
	}
	delete pIn;
	delete pOut;
	
}
