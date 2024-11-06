/*
Lab Week 14
TTT game with special function
Brian Reeder - 5/3/24

*/

#include <iostream> //for cout, cin
#include <string>   //for string
#include <fstream>  //for file write and read functions

using namespace std;


void display();	//void module
void choose(); //module that prompts, keeps track of turns, 
void winCheck();    //module to detect wins



//global vars
std::string TTT = { "0123456789" }; //using a string and string arrays (chars) for our ttt board, this allows us to swap out "numbers" for X and O, starts at 0 since TTT[0] would be 1 if we didnt

int turnCount = 0;      //variable that will alternate allowing us to have turns

int winCount = 1;   //used to mark when to end our rud. loop. this allows us to run the game until a win is detected, 0 or a dif value indicates a win is detected and the loop breaks



int main()
{
    char select;
    ifstream readOBJ;       //this object has the abiity to read scores from our file

    //system("Color 57");  // x or 1st value changes bckrnd, and y changes txt - using primarily for backround (ansi only colors backround of printed text)
    cout << "\tTic Tac Toe";
  

    //turn
choice_loop:

    if (winCount == 1)
    {
        display();      //calls display
        choose();       //calls prompt/turn

        winCheck();   //first thing we do is test for a win, automatically set to one so game will start as expected

        turnCount++;    //++ adds one to our selection var, which starts as 0
        goto choice_loop;     //rudimentary loop
    }
    if (winCount == 0)
    {
        std::cout << "\n\nWould you like to play again? (y/n): ";
        std::cin >> select;

        if (select == 'y' || select == 'Y')
        {
            TTT = { "0123456789" }; //resets board
            winCount = 1;           //resets game loop

            goto choice_loop;       //starts game over
        }

        if (select == 'n' || select == 'N')
        {
            char readBuffer = {};   //using a char instead of array or stirng, this way we can search for certain char markers for new lines and spaces

            std::cout << "\n\nThanks for playing!\n";

            readOBJ.open("TTTwins.txt", std::ios::in);     //using read mode with the f stream object, opens file
            std::cout << "\n\n";

            while (!readOBJ.eof()) //keeps reading while the eof marker is not detected
            {
                readOBJ >> readBuffer; //sets the current read char into the char variable


                if (readBuffer == '?')   //if our delimiter is detected, then we start the new line
                {
                    std::cout << "\n";
                    continue;
                }
                if (readBuffer == ';')  //if the semicolon is detected we print out a space, then continue to stop from printing the semicolon
                {
                    std::cout << " ";
                    continue;
                }

                std::cout << readBuffer;    //if a space our new line marker is not detected, we simply output the character we are on

            }

            readOBJ.close();   //close the file
        }
    }

    //exit
    char exit;

    std::cout << "\n\n\n *If your are done with the program enter any character: ";
    std::cin >> exit;


    return 0;
}

//display module -----------------------------------------------------------------------------------------------------------------------------
void display()
{
    cout << std::endl;
    cout << "___________________\n";  //acts as the top border, positioned with same amount of characters
    cout << "|                 |\n";  //acts as side walls
    cout << "|" << TTT[1] << "       " << TTT[2] << "       " << TTT[3] << "|\n";
    cout << "|                 |\n";
    cout << "|" << TTT[4] << "       " << TTT[5] << "       " << TTT[6] << "|\n";
    cout << "|                 |\n";
    cout << "|" << TTT[7] << "       " << TTT[8] << "       " << TTT[9] << "|\n";
    cout << "|_________________|\n"; //bottom border; same wall width, only difference is underscore
    
}




//user choice module -----------------------------------------------------------------------------------------------------------------------------
void choose()
{
failsafe_loop:

    char replacementCharacter = { '?' };        //this character regulates which char will replace the selected nmumber, based on the turnCount value, the repChar is changed to that corresponding turn's value
    int selection = 0;  //declare our selection var, used to choose the value we want.

    if ((turnCount % 2) == 0)     //allows for an increment value (turnCount) to be used to regulate whos turn is displayed.
    {                                        //we start with 0's turn then alternate using odd and even detection with a modulus operator
        std::cout << "\n  [It is O's turn]\n";
        replacementCharacter = 'O';
    }
    else
    {
        std::cout << "\n  [It is X's turn]\n";
        replacementCharacter = 'X';
    }

    std::cout << "\n    Please enter \n     a number: ";    //prompts
    std::cin >> selection;


    if ((TTT[selection]) == 'X' || (TTT[selection]) == 'O' || selection > 9 || selection < 1)    //if statement acts as a test, with multiple conditions. if these are met we say invalid and loop back to our label
    {
        std::cout << "\n+-------------------+" << "\n  Invalid Selection" << "\n+-------------------+\n";
        goto failsafe_loop;     //loops back to top of function
    }

    TTT[selection] = replacementCharacter;      //sets the int we selected (which corresponds to the boards values hence TTT[?]) equal to the replacement char which is automatically set from the previous steps
    std::cout << "=-=-=-=-=-=-=-=-=-=-=\n\n";
}



//win detection module -------------------------------------------------------------------------------------------------------------------
void winCheck()
{
    int loopIncrement = 0;  //increment used to run our check with 'X' then switch to 'O', resets back to 0 every time this block is called so we can keep checking for wins

    char wVar = 'X';      //var we will use to swap x and o out for our test

    ofstream writeOBJ;
   // char writeBuffer;

    writeOBJ.open("TTTwins.txt", std::ios::app);


winCheck_loop:

    if (loopIncrement == 0 || loopIncrement == 1) //basically runs the win check twice, once for x and once for O, since at the end of the x tests we changed wVar to O
    {

        if ((TTT[1] == wVar) and (TTT[2] == wVar) and (TTT[3] == wVar))
        {
            std::cout << "   " << wVar << " has won with \n    row: 1, 2, 3";
            winCount = 0;
            writeOBJ << "\n" << wVar << ";has;won;with;row:;1,;2,;3?";
        }
        if ((TTT[4] == wVar) and (TTT[5] == wVar) and (TTT[6] == wVar))
        {
            std::cout << "   " << wVar << " has won with \n    row: 4, 5, 6";
            winCount = 0;
            writeOBJ << "\n" << wVar << ";has;won;with;row:;4,;5,;6?";
        }
        if ((TTT[7] == wVar) and (TTT[8] == wVar) and (TTT[9] == wVar))
        {
            std::cout << "   " << wVar << " has won with \n    row: 7, 8, 9";
            winCount = 0;
            writeOBJ << "\n" << wVar << ";has;won;with;row:;7,;8,;9?";
        }



        if ((TTT[1] == wVar) and (TTT[4] == wVar) and (TTT[7] == wVar))
        {
            std::cout << "   " << wVar << " has won with \n  column : 1, 4, 7";
            winCount = 0;
            writeOBJ << "\n" << wVar << ";has;won;with;column:;1,;4,;7?";
        }
        if ((TTT[2] == wVar) and (TTT[5] == wVar) and (TTT[8] == wVar))
        {
            std::cout << "   " << wVar << " has won with \n  column : 2, 5, 8";
            winCount = 0;
            writeOBJ << "\n" << wVar << ";has;won;with;column:;2,;5,;8?";
        }
        if ((TTT[3] == wVar) and (TTT[6] == wVar) and (TTT[9] == wVar))
        {
            std::cout << "   " << wVar << " has won with \n  column : 3, 6, 9";
            winCount = 0;
            writeOBJ << "\n" << wVar << ";has;won;with;column:;3,;6,;9?";
        }


        if ((TTT[1] == wVar) and (TTT[5] == wVar) and (TTT[9] == wVar))
        {
            std::cout << "   " << wVar << " has won with \n   cross : 1, 5, 9";
            winCount = 0;
            writeOBJ << "\n" << wVar << ";has;won;with;cross:;1,;5,;9?";
        }
        if ((TTT[7] == wVar) and (TTT[5] == wVar) and (TTT[3] == wVar))
        {
            std::cout << "   " << wVar << " has won with \n   cross : 7, 5, 3";
            winCount = 0;
            writeOBJ << "\n" << wVar << ";has;won;with;cross:;7,;5,;3?";
        }

        wVar = 'O'; //chnages our win var test value to O so we can test if O won
        loopIncrement++;    //adds one to our loop increment breaking out of our loop after this run
        goto winCheck_loop;
    }

    writeOBJ.close();

    return;
}