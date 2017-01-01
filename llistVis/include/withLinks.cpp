#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include <cgicc/CgiDefs.h>
#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>

using namespace std;
using namespace cgicc;


#include "llist2.h"

/* The whole program gets executed with each POST. */

int main()
{

  // what we cout will be sent back as a JSON object
    cout << "Content-Type:application/json\n\n";

  llist L;   // this is my list

  // What we receive from the client
  Cgicc receivedData;

  // It has the choice and list parts
   form_iterator fi = receivedData.getElement("choice");
   form_iterator f2 = receivedData.getElement("list");

   string z ="";  // to be sent back to the client (JSON)

  if ( !f2->isEmpty() && f2 != (*receivedData).end() &&
      !fi->isEmpty() && fi != (*receivedData).end()  )
  {
    z =  z + "{" + " \"previous\":" + "\"" + **f2 + "\"" + "," ;

    /* what we want to be able to do here is to set the current
       llist to be the list sent from the client (**f2) before executing
       the following lines  */
   string prev_list = **f2;
   if (prev_list != "[]")
     { for (int i = 1; prev_list[i] != ']'; i=i+2)
         {
           if (prev_list[i] == 'S') L.addRear('S');
           else L.addRear('E');
         } }

   // Changes to the llist as per menu item
   if (**fi == "1")
       {
         // add rear
         L.addRear('E');
         // display the list
         L.displayAll2(z);
       }
     else if (**fi == "2")
       { // delete rear
         char x;
         L.deleteRear(x);
         // display the list
         L.displayAll2(z);
          }
   if (**fi == "3")
       {
         // add front
         L.addFront('E');
         // display the list
         L.displayAll2(z);
       }
     else if (**fi == "4")
       { // delete front
         char x;
         L.deleteFront(x);
         // display the list
         L.displayAll2(z);
          }
     else if (**fi == "5")
       { // empty
         L.~llist();
         L.displayAll2(z);
       }
     else if (**fi == "6")
       { // set S
         L.setS();
         L.displayAll2(z);
       }
     else if (**fi == "7")
       { // Add before 3rd
         L.addbeforeIth(3, 'E');
         L.displayAll2(z);
       }
     else if (**fi == "8")
       { // Delete 3rd
         char x;
         L.deleteIth(3, x);
         L.displayAll2(z);
       }
     else if (**fi == "9")
       {
         // move Front down if possible
         L.moveFront();
         L.displayAll2(z);
       }

  }

  return 0;

}

