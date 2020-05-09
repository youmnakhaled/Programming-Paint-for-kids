#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"
#include"Figures/CRectangle.h"
#include "Figures\CFigure.h"
#include "GUI\input.h"
#include "GUI\output.h"
#include<cstdlib>
//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxFigCount = 200 };	//Max no of figures

private:
	int FigCount;		//Actual number of figures
	CFigure* FigList[MaxFigCount];	//List of all figures (Array of pointers)

	CFigure* SelectedFig; //Pointer to the selected figure
	CFigure* SetSelectedFig;
	CFigure* Clipboard;   //Pointer to the copied/cut figure

	//Pointers to Input and Output classes
	Input *pIn;
	Output *pOut;

public:	
	ApplicationManager(); 
	~ApplicationManager();
	
	// -- Action-Related Functions
	//Reads the input command from the user and returns the corresponding action type
	ActionType GetUserAction() const;
	void ExecuteAction(ActionType) ; //Creates an action and executes it
	void SaveAll(ofstream &OutFile);

	
	// -- Figures Management Functions
	void AddFigure(CFigure* pFig);          //Adds a new figure to the FigList
	CFigure *GetFigure(int x, int y) const; //Search for a figure given a point inside the figure
	CFigure *GetSelectedFig();
	void SetSelectedFigure(CFigure* c );
	void Setclipboard(CFigure *Figure);
	CFigure* Getclipboard() const;
	void TranslateShape(CFigure *fig,Point P1); //Translate figure from point to another.
	
	void Deletefigure(CFigure* d);
	//void Deletes();
	// -- Interface Management Functions
	Input *GetInput() const; //Return pointer to the input
	Output *GetOutput() const; //Return pointer to the output
	void UpdateInterface() const;	//Redraws all the drawing window
	//void UpdateOrderOfArray () ; // we'll use it to update figure list after deleting
	color randomcolor(int & count); //gets random color
	int randomfigure(int &count); //gets random figure
	void disappear(CFigure*f); ////hides figures
	bool check(CFigure*f); //checks for figures
};

#endif