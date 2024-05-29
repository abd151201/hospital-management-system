#include <iostream>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#define MAXPATIENTS 100
using namespace std;

class patient      
{
public:
   char FirstName[50];
   char LastName[50];
   char ID[20];
};

class queue
{
   public:
   queue (void);
   int AddPatientAtEnd (patient p);
   int AddPatientAtBeginning (patient p);
   patient GetNextPatient (void);
   int RemoveDeadPatient (patient * p);
   void OutputList (void);
   char DepartmentName[50];
   private:
   int NumberOfPatients;
   patient List[MAXPATIENTS];
};

queue::queue ()
{
   
   NumberOfPatients = 0;
}

int queue::AddPatientAtEnd (patient p)
{
  
  if (NumberOfPatients >= MAXPATIENTS)
   {
    
      return 0;
   }
      
      else
      List[NumberOfPatients] = p;  NumberOfPatients++;
      return 1;
}

int queue::AddPatientAtBeginning (patient p)
{
   int i;
   if (NumberOfPatients >= MAXPATIENTS)
   {
      
      return 0;
   }

   for (i = NumberOfPatients-1; i >= 0; i--)
   {
      List[i+1] = List[i];
   }
   
   List[0] = p;  
   NumberOfPatients++;
   return 1;
}

patient queue::GetNextPatient (void)
{
   
   int i;  patient p;
   if (NumberOfPatients == 0) {
  
   strcpy(p.ID,"");
   return p;}
  
   p = List[0];
   
   NumberOfPatients--;
   for (i=0; i<NumberOfPatients; i++)
   {
      List[i] = List[i+1];
   }
   
   return p;
}

int queue::RemoveDeadPatient (patient * p)
{
   // FOUND ACTS AS BOOLEAN EXPRESSION
   int i, j, found = 0;
   
   // HERE IT WILL SERACH FOR THE PATIENT 
   for (i=0; i<NumberOfPatients; i++)
	{
      		if (stricmp(List[i].ID, p->ID) == 0)
		{
	 
	 	*p = List[i];  found = 1;
	 	
	 	NumberOfPatients--;
	 		for (j=i; j<NumberOfPatients; j++)
				{
	    				List[j] = List[j+1];
				}
		}
	}
   return found;
}

void queue::OutputList (void)
{
  
   int i;
   if (NumberOfPatients == 0)
	{
      	cout << "Queue is empty! ";
	}
   else
	{

		for (i=0; i<NumberOfPatients; i++)
		{
			cout << " " << List[i].FirstName;
	 		cout << " " << List[i].LastName;
	 		cout << " " << List[i].ID;
		}
	}
}

// MEMEBER FUNCTIONS WHICH WILL BE USED LATER ON

patient InputPatient (void)
{
   patient p;
   cout << "Please Enter Data For New Patient's First Name: "<<endl;
   cin.getline(p.FirstName, sizeof(p.FirstName));
   cout << "Last Name: "<<endl;
   cin.getline(p.LastName, sizeof(p.LastName));
   cout << "Medical Record No: "<<endl;
   cin.getline(p.ID, sizeof(p.ID));
   
   if (p.FirstName[0]==0 || p.LastName[0]==0 || p.ID[0]==0)
	{
      	
      		strcpy(p.ID,"");
      		cout << "Error : Data not valid. Operation cancelled.";
      		getch();
	}
   return p;
}

void OutputPatient (patient * p)
{
   if (p == NULL || p->ID[0]==0)
	{
      		cout << "No Patient";
      		return;
	}
   else
   cout << "Patient Data:"<<endl;
   cout << "First name: " << p->FirstName<<endl;
   cout << "Last name: " << p->LastName<<endl;
   cout << "Medical Record No: " << p->ID<<endl<<endl;
   cout<<"*** ----------_--------- ***"<<endl<<endl;
}

int ReadNumber()
{
  
   char buffer[20];
   cin.getline(buffer, sizeof(buffer));
   return atoi(buffer);
}

void DepartmentMenu (queue * q)
{

   int choice = 0, success;  patient p;
   while (choice != 6)
	{
      	   
      	   // DISPLAY MENU
      	   cout << "Reception of " << q->DepartmentName<<endl<<endl;
      	   cout << "Please enter your choice:"<<endl;
      	   cout << "1:  Add normal Patient"<<endl;
      	   cout << "2:  Add critically ill Patient"<<endl;
      	   cout << "3:  Bring Patient for operation"<<endl;
      	   cout << "4:  Remove dead Patient from queue"<<endl;
      	   cout << "5:  Display Patient queue"<<endl;
      	   cout << "6:  Change department or exit"<<endl;
      	  
      	   choice = ReadNumber();
      		
      	switch (choice)
	  {
      		case 1:   // ADDING NORMAL PATEINTS
	 	p = InputPatient();
	 	if (p.ID[0])
		   {
	    		success = q->AddPatientAtEnd(p);
	    		
	    		  if (success)
			    {
	       			cout << "Patient added:"<<endl;

			    }
	        else
		   {
	       		
	       		cout << "Error: The queue is full. Cannot add patient:";
		   }
	    		OutputPatient(&p);
	    		cout << "Press any key to proceed :"<<endl;
	    		getch();
	  }
	 break;

      case 2:   // ADDING CRITICAL PATEINTS
	 p = InputPatient();
	 if (p.ID[0])
	     {
	    	success = q->AddPatientAtBeginning(p);
	    	
	    	  if (success)
			{
	       		  cout << "Patient added:"<<endl;
	     		}
	 	  else
	     		{
	       		  
	       		  cout << "Error: The queue is full. Cannot add patient:"<<endl;
			}

			  OutputPatient(&p);
	    		  cout << "Press any key to proceed :"<<endl;
	    		  getch();
	     }
	 break;

      case 3:   // IN THIS CASE PATIENT WILL GO FOR OPERATION
	 p = q->GetNextPatient();
	 
	 if (p.ID[0])
	    {
	       cout << "Patient to be operated:  ";
	       OutputPatient(&p);}
	 else
	    {
	       cout << "There is no patient to operate.";
	    }
	       cout << "Press any key to proceed :"<<endl;
	       getch();
	       break;

      case 4:   // IN THIS CASE DEAD PATEINT WILL BE REMOVED
	 p = InputPatient();
	 if (p.ID[0])
	   {
	        success = q->RemoveDeadPatient(&p);
	    
	          if (success)
		      {
	       		cout << "Removed ";
		      }
	    	  else
		      {
	       		//PROMPT FOR ERROR CASE
	       		cout << "Error: Cannot find patient:";
		      }
	   	OutputPatient(&p);
	    	cout << "Press any key to proceed : "<<endl;
	    	getch();
	   }
	 break;

      case 5:   
	 q->OutputList();
	 cout<<endl<<endl;
	 cout << "Press any key to proceed : "<<endl;
	 getch();  break;
	 }
      }
}

int main ()
{
   int i, MenuChoice = 0;
   // HERE WE WILL DEFINE 3 QUEUES
   queue departments[3];
   
   strcpy (departments[0].DepartmentName, "CARDIOLOGY OPD");
   strcpy (departments[1].DepartmentName, "ENT OPD");
   strcpy (departments[2].DepartmentName, "EYE OPD");

   while (MenuChoice != 4)
	{
      	   // DISPLAY MENU 
      	   cout << " *COMBINED MILITARY HOSPITAL MANAGEMNET SYSTEM* "<<endl<<endl;
      	   cout << "Please enter your choice:"<<endl;
          for (i = 0; i < 3; i++)
		{
	 	   
	 	   cout << "" << (i+1) << ":  " << departments[i].DepartmentName<<endl;
		}
      	  cout << "4:  Exit"<<endl;
      	  // HERE USER WILL SELECT  AN OPTION 
      	  MenuChoice = ReadNumber();
      	  
      		if (MenuChoice >= 1 && MenuChoice <= 3)
		    {
	 		
	 		DepartmentMenu (departments + (MenuChoice-1));
		    }
	}

return 0;
}
