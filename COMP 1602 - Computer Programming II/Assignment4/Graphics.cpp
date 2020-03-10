#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <ctime>
	using namespace std;
	
#define MAXROWS    10									// maximum possible row size
#define MAXCOLS    10 									// maximum possible column size

#define NUMROWS 	6									// number of rows on the board
#define NUMCOLS 	6									// number of columns on the board
#define NUMMINES	5									// numbers of mines to place on the board

#define WIDTH	    (NUMCOLS * 50) + 200				// width of window (NUMCOLS * 50 + 200)	
#define HEIGHT	    (NUMROWS * 50) + 200				// height of window (NUMROWS * 50 + 200)	

const char g_szClassName[] = "myWindowClass";			// for windows program

struct Cell {											// represents each cell on the game board
	
   bool hasMine;
   bool isMarked;
   bool isHidden;
   int number;
};

struct MouseEvent {										// stores information when the mouse is clicked
   bool leftButtonPressed;
   bool rightButtonPressed;
   int row;
   int col;
};

// function prototypes

Cell createCell();
void initGameBoard(Cell cells[MAXROWS][MAXCOLS], int numRows, int numCols);
void placeMinesOnBoard(Cell cells[MAXROWS][MAXCOLS], int numRows, int numCols, int numMines);
void setNumbers(Cell cells[MAXROWS][MAXCOLS], int numRows, int numCols);
void clearBlanks(Cell cells[MAXROWS][MAXCOLS], int numRows, int numCols, int row, int col);
bool hasWon (Cell cells[MAXROWS][MAXCOLS], int numRows, int numCols);
int select(Cell cells[MAXROWS][MAXCOLS], int numRows, int numCols, int row, int col);
void mark(Cell cells[MAXROWS][MAXCOLS], int row, int col);

Cell cells[MAXROWS][MAXCOLS];							// 2D array of cells for game (global)
int numRows, numCols, numMines;							// actual rows, columns, and mines in game (global)
int gameStatus;											// 0 (game on), 1 (game won), -1 (game lost)

HBRUSH hbrBorder = CreateSolidBrush(RGB(0,128,0));		// colour for borders of game board
HBRUSH hbrHidden = CreateSolidBrush(RGB(0,128,128));	// colour for hidden cells
HBRUSH hbrMarked = CreateSolidBrush(RGB(128,0,0));		// colour for marked cells
HBRUSH hbrVisible = CreateSolidBrush(RGB(112,128,144));	// colour for visible cells
HBRUSH hbrMine = CreateSolidBrush(RGB(255,0,255));		// colour for cells with mines (at end of game)


/* =========================================================================
   Functions to be written for Assignment #4:

	========================================================================
*/


// This function initializes a single cell in the 2D minesweeper board.

Cell createCell() {
    Cell c;
    return c;
}



// This function initializes all the cells in the 2D minesweeper board.

void initGameBoard(Cell cells[MAXROWS][MAXCOLS], int numRows, int numCols) {
	return;
}



// This function randomly places a certain amount of mines (specified as a
// parameter, numMines) on the 2D board.

void placeMinesOnBoard(Cell cells[MAXROWS][MAXCOLS], int numRows, int numCols, int numMines) {
	return;
 }



// Given a particular (row, col) location, this function determines if the
// location is valid for the given board. A location is valid if it is within
// the range of the rows and columns of the board.
     
bool isValidLocation (int numRows, int numCols, int row, int col) {
        return false;
}



// This function finds the number that should be assigned to a given cell on
// the board (which is not a mine). This number is calculated based on the 
// number of adjacent mines.                     
                        
int getNumber (Cell cells[MAXROWS][MAXCOLS], int numRows, int numCols, int row, int col) {
    return 0;
}



// This function sets the number of all the cells on the board (which is not
// a mine). It calls the getNumber function to get the number for a particular
// cell.
    
void setNumbers(Cell cells[MAXROWS][MAXCOLS], int numRows, int numCols) { 
	return;
}



// This function is called whenever the user left-clicks on a cell containing
// a blank (i.e., the number 0 has been assigned to cell. THE CODE GIVEN SHOULD
// NOT BE MODIFIED.

void clearBlanks(Cell cells[MAXROWS][MAXCOLS], int numRows, int numCols, int row, int col) {
     
     if (row - 1 >= 0) {
         if ((!cells[row-1][col].hasMine) && (cells[row-1][col].isHidden)) {             
            cells[row-1][col].isHidden = false;
            if (cells[row-1][col].number == 0)
                clearBlanks(cells, numRows, numCols, row-1, col);
         }
     }
 
     if (row + 1 < numRows) {
         if ((!cells[row+1][col].hasMine) && (cells[row+1][col].isHidden)) {             
            cells[row+1][col].isHidden = false;
            if (cells[row+1][col].number == 0)
                clearBlanks(cells, numRows, numCols, row+1, col);
         }
     } 
     
     if (col - 1 >= 0) {
         if ((!cells[row-1][col].hasMine) && (cells[row-1][col].isHidden)) {             
            cells[row-1][col].isHidden = false;
            if (cells[row-1][col].number == 0)
                clearBlanks(cells, numRows, numCols, row-1, col);
         }
     }
 
     if (row + 1 < numRows) {
         if ((!cells[row+1][col].hasMine) && (cells[row+1][col].isHidden)) {             
            cells[row+1][col].isHidden = false;
            if (cells[row+1][col].number == 0)
                clearBlanks(cells, numRows, numCols, row+1, col);
         }
     }      
     
     if (col - 1 >= 0) {
         if ((!cells[row][col-1].hasMine) && (cells[row][col-1].isHidden)) {             
            cells[row][col-1].isHidden = false;
            if (cells[row][col-1].number == 0)
                clearBlanks(cells, numRows, numCols, row, col-1);
         }
     }     

     if (col + 1 < numCols) {
         if ((!cells[row][col+1].hasMine) && (cells[row][col+1].isHidden)) {             
            cells[row][col+1].isHidden = false;
            if (cells[row][col+1].number == 0)
                clearBlanks(cells, numRows, numCols, row, col+1);
         }
     }     

}



// This function determines if the current situation on the board is a "win"
// situation. A "win" situation occurs when all the hidden cells are mines.

bool hasWon (Cell cells[MAXROWS][MAXCOLS], int numRows, int numCols) { 
	return false;
}     



// This function is called when the user left-clicks on the mouse on a
// particular cell. It is possible that the cell is blank, has a number
// assigned to it, or contains a mine. If there are no more mines to be 
// discovered, it results in a "win" situation. It returns 0 to indicate
// that the game is still in progress, -1 to indicate that the game has
// been lost, or 1 to indicate that the game has been won

int select(Cell cells[MAXROWS][MAXCOLS], int numRows, int numCols, int row, int col) {
    return 0;
}



// This function is called when a user right-clicks on the mouse to indicate
// that a cell should be "marked" as having a mine. If a cell is already marked,
// it should be un-marked.

void mark(Cell cells[MAXROWS][MAXCOLS], int row, int col) {
	return;
}


/*  =========================================================================================
	End of code to be written for Assignment #4. The rest of the code should not be modified.
	=========================================================================================
*/

void initGame() {
	
	numRows = NUMROWS;												// number of rows on board
	numCols = NUMCOLS;												// number of columns on board
	numMines = NUMMINES;											// number of mines present
	
	initGameBoard(cells, numRows, numCols);							// initialize the game board
	placeMinesOnBoard(cells, numRows, numCols, numMines);			// place mines on game board
	setNumbers(cells, numRows, numCols);							// determine numbers for each cell	
	
	gameStatus = 0;													// game on
		
}



void drawGameWindow(HDC hdc, HWND hwnd) {

	RECT rect;       										// inner rectangle for the game window 

	TextOut(hdc, 100, 20, TEXT("MINESWEEPER"), 11);			// draw title of game

	HPEN hPen = CreatePen(PS_SOLID, 0, RGB(255,20,147));	// create pen to draw outer rectangles
	SelectObject(hdc, hPen);

	int endX = (NUMCOLS * 50) + 100 + 5;					// ending x-coordinate for outer rectangle
	int endY = (NUMROWS * 50) + 50 + 5;						// ending y-coordinate for outer rectangle
	
	Rectangle(hdc, 95, 45, endX, endY);						// draw outer rectangles for grid
	Rectangle(hdc, 96, 46, endX-1, endY-1);
	Rectangle(hdc, 97, 47, endX-2, endY-2);
	Rectangle(hdc, 98, 48, endX-3, endY-3);
	Rectangle(hdc, 99, 49, endX-4, endY-4);

	int row, col;											// to traverse cells array
	int x, y;												// coordinates of inner rectangles
  	
	y = 50;													// starting y-coordinate (first row)
 	for (row=0; row<numRows; row=row+1) {
		x = 100;											// starting x-coordinate (each column)	
		for (col=0; col<numCols; col=col+1) {
			Rectangle(hdc, x, y, x + 50, y + 50);			// create border for inner rectangle
			SetRect(&rect, x+3, y+3, x + 47, y + 47);		// create inner rectangle
			
            if (cells[row][col].isHidden == true) { 		// unexposed cell
                if (cells[row][col].isMarked == true) { 	// cell is marked
                	FillRect(hdc, &rect, hbrMarked);        // fill rectangle with appropropriate colour                                    
                }
                else {
                    FillRect(hdc, &rect, hbrHidden);		// cell is hidden (but not marked)
                }                                                              
            }
            else { 											// cell is visible
                if (cells[row][col].number == 0) { 			// cell is blank
                    FillRect(hdc, &rect, hbrVisible);		// fill rectangle with appropropriate colour 
                }
                else {
                    if (cells[row][col].number > 0) {		// cell is visible but has a number > 0
                         char num [2];
                         sprintf(num, "%d", cells[row][col].number);
                         FillRect(hdc, &rect, hbrVisible);	// fill rectangle with appropropriate colour
						 SetBkMode(hdc, TRANSPARENT);
                         TextOut(hdc, x+20, y+17, TEXT(num), 1);
						 									// draw number on cell
                    }
                }
			}
			
			if (gameStatus == -1) { 						// end of game: player has lost
                   if (cells [row][col].hasMine == true) { 	// show where the mines are
                      FillRect (hdc, &rect, hbrMine);
                      if (cells [row][col].isMarked == true) {
						 SetBkMode(hdc, TRANSPARENT);
                         TextOut(hdc, x+20, y+17, TEXT("+"), 1);                      	
                      }                         
                   }
                   else 									// show incorrectly marked mines
                   if (cells [row][col].isMarked == true) {
						SetBkMode(hdc, TRANSPARENT);
                        TextOut(hdc, x+20, y+17, TEXT("-"), 1);      
                   }
            }

			x = x + 50;										// advance to inner rectangle for next column
		}
		y = y + 50;											// advance to next row of inner rectangles
	}

	int messageX = 100;										// x-coordinate to start displaying message
	int messageY = 50 + (NUMROWS * 50) + 25;				// y-coordinate to start displaying message
	
	if (gameStatus == 1) {									// end of game: player has won
		TextOut(hdc, messageX, messageY, TEXT("Congratulations! You have won!"), 30);
		PlaySound("ApplauseClip.wav", NULL, SND_FILENAME);
	}
	else 
	if (gameStatus == -1) {									// end of game: player has lost
		x = (500 - numCols * 50) / 2;
		TextOut(hdc, messageX, messageY, TEXT("Sorry! You have lost the game."), 30);	
		PlaySound("GameOverClip.wav", NULL, SND_SYNC);
	}
	
	DeleteObject(hPen);
}



void leftClick(HWND hwnd, MouseEvent event) {

	HDC hdc = GetDC (hwnd);

	if (gameStatus == 1 || gameStatus == -1)				// ignore, if the game has been won or lost
		return;

	if (event.row >= numRows || event.col >= numCols)		// only respond to mouse clicks on the board
		return;
		
	gameStatus = select (cells, numRows, numCols, event.row, event.col);
	
	drawGameWindow(hdc, hwnd);								// draw the game window

}



void rightClick(HWND hwnd, MouseEvent event) {
	
	HDC hdc = GetDC (hwnd);

	if (gameStatus == 1 || gameStatus == -1)				// ignore, if the game has been won or lost
		return;

	if (event.row >= numRows || event.col >= numCols)		// only respond to mouse clicks on the board
		return;
	
	mark (cells, event.row, event.col);
	
	drawGameWindow(hdc, hwnd);								// draw the game window
	
}



LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	
	
	switch(msg)
	{
		case WM_CREATE:
		{

			initGame();
			break;
		}

        case WM_LBUTTONDOWN:
        {            
			long xPos = GET_X_LPARAM(lParam); 
			long yPos = GET_Y_LPARAM(lParam);
	
			if ((xPos < 100 || xPos > (NUMCOLS * 50) + 100) ||
				(yPos < 50 || yPos > (NUMROWS * 50) + 50))
				break;
					
			xPos = xPos - 100;
			yPos = yPos - 50;
			xPos = xPos / 50;
			yPos = yPos / 50;
			
			MouseEvent event;
			
			event.leftButtonPressed = true;
			event.rightButtonPressed = false;
			event.row = yPos;
			event.col = xPos;
            leftClick(hwnd, event);           
        }
        break;
        
        case WM_RBUTTONDOWN:
        {
            long xPos = GET_X_LPARAM(lParam); 
			long yPos = GET_Y_LPARAM(lParam);

			if ((xPos < 100 || xPos > (NUMCOLS * 50) + 100) ||
				(yPos < 50 || yPos > (NUMROWS * 50) + 50))
				break;

			xPos = xPos - 100;
			yPos = yPos - 50;
			xPos = xPos / 50;
			yPos = yPos / 50;

			MouseEvent event;
			
			event.leftButtonPressed = false;
			event.rightButtonPressed = true;
			event.row = yPos;
			event.col = xPos;
            rightClick(hwnd, event);           
        }
        break;

		case WM_PAINT:
		{
 			HDC hdc;
 			PAINTSTRUCT ps;
 		
			hdc = BeginPaint(hwnd, &ps);
 			drawGameWindow(hdc, hwnd);							// draw the game window
 			EndPaint(hwnd, &ps);
 			return 0;		    
 		}
 		break;
 		
		case WM_CLOSE:
			DestroyWindow(hwnd);
		break;

		case WM_DESTROY:
			PostQuitMessage(0);
		break;

		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;

	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.style		 = 0;
	wc.lpfnWndProc	 = WndProc;
	wc.cbClsExtra	 = 0;
	wc.cbWndExtra	 = 0;
	wc.hInstance	 = hInstance;
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = g_szClassName;
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION);

	if(!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(
		0,
		g_szClassName,
		"COMP 1602 Assignment 4 (Due March 27, 2019)",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, WIDTH, HEIGHT,
		NULL, NULL, hInstance, NULL);

	if(hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while(GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	return Msg.wParam;
}

