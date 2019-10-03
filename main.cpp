
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <cmath>

using namespace std;

struct Patient{
    int number;
    char name[30];
    char surname [30];
    int dateOfBirth;
    char gender;
    float hight;
    float weight;
    float massIndx;
};
void deletePatient(Patient *patientList, int patientCount);
int maxPatientNo(Patient *patientList, int patientCount);
void findPatient(Patient *patientList, int patientCount);
void printOnePatient(Patient *patientList, int patientCount, int patientNo);
void editPatient(Patient *patientList, int patientCount);
void coutMassIndex(Patient *patientList, int patientCount);
void insertNewPatient(Patient *patientList, int patientCount);
void printPatients(Patient *patientList, int patientCount);
void savePatientList(Patient *patientList,  int patientCount);
void loadPatientList(Patient *patientList);
int loadPatientCount();


int main() {

    char inStr[20], usrCmd;
    bool systemIsWorking = true;
    int patientCount = loadPatientCount();
    printf("patientCount %d\n", patientCount);
    struct Patient *patientList = (struct Patient*) malloc(sizeof(struct Patient) * patientCount);
    loadPatientList(patientList);
    printf("Information system of patients starts to work\n");

    while (systemIsWorking != false)
    {

        printf("\nMAIN MENIU: Please choose the action: \n");
        printf("\t 1 - print the list of patients on the screen \n");
        printf("\t 2 - enter information of a new patient \n");
        printf("\t 3 - edit information of the patient \n");
        printf("\t 4 - search for the patient \n");
        printf("\t 5 - calculate body mass index \n");
        printf("\t 6 - delete information of the patient\n");
        printf("\t 7 - save information into the file \n");
        printf("\t q - QUIT THE PROGRAM \n");

        // standard c++ input
        cin >> inStr;
        usrCmd = inStr[0];

        switch (usrCmd) {
            case '1' :
                printPatients(patientList, patientCount);
                break;
            case '2' :
                patientCount = patientCount +1;
                patientList = (struct Patient*) realloc(patientList, (sizeof(struct Patient) * (patientCount)));
                //printf("Masyvo atmintis padidinta\n");
                insertNewPatient(patientList, patientCount);
                //savePatientList(patientList, patientCount);
                break;
            case '3' :
                editPatient(patientList, patientCount);
                break;
            case '4' :
                findPatient(patientList, patientCount);
                break;
            case '5' :
                coutMassIndex(patientList, patientCount);
                break;
            case '6' :
                deletePatient(patientList, patientCount);
                patientCount = patientCount -1;
                break;
            case '7' :
                savePatientList(patientList, patientCount);
                printf("The information was saved to the file");
                break;
            case 'q' :
                printf("Information system of patients quits\n");
                systemIsWorking = false;
                return 0;
            default :
                    printf("Wrong choice, please enter valid command\n");
        }
    }
}

void deletePatient(Patient *patientList, int patientCount)
{
    printf("please enter No. of patient you want to delete\n");
    char inStr[20];
    cin >> inStr;
    int delIndx = (int) (atoi (inStr) -1);

    for (int i=delIndx; i<patientCount-1; i++)
    {
        patientList[i].number = patientList[i+1].number;
        strcpy(patientList[i].name, patientList[i+1].name);
        strcpy(patientList[i].surname, patientList[i+1].surname);
        patientList[i].dateOfBirth = patientList[i+1].dateOfBirth ;
        patientList[i].gender =  patientList[i+1].gender;
        patientList[i].hight = (float) patientList[i+1].hight;
        patientList[i].weight =  (float) patientList[i+1].weight;
        patientList[i].massIndx = (float) patientList[i+1].massIndx;
    }
    int i = patientCount - 1;
    patientList[i].number = 0 ;
    strcpy(patientList[i].name, "");
    strcpy(patientList[i].surname, "");
    patientList[i].dateOfBirth = 0 ;
    patientList[i].gender =  'u';
    patientList[i].hight = (float) 0.0;
    patientList[i].weight =  (float) 0.0;
    patientList[i].massIndx = (float) 0.0;

    printf("The patient No.: %d was deleted", delIndx +1 );
}

void findPatient(Patient *patientList, int patientCount)
{
    char inStr[30];
    bool patientFound = false;

    printf("SEARCH MENU\n");
    printf("\t 1 - according to the name\n");
    printf("\t 2 - according to the surname\n");
    printf("\t 3 - according to the year og birth\n");
    printf("\t 4 - according to the gender\n");
    printf("\t 5 - according to the height\n");
    printf("\t 6 - according to the weight\n");
    printf("\t 7 - according to the mass index\n");
    printf("\t q - quit the search\n");

    cin >> inStr;

    switch (inStr[0]) {
        case '1' :
            printf("please enter the name:\n");
            cin >> inStr;
            for (int i=0; i <patientCount; i++)
            {
                if (strcmp(patientList[i].name, inStr) == 0)
                {
                    printf("patient was found:\n");
                    printOnePatient(patientList, patientCount, patientList[i].number);
                    patientFound = true;
                }
            }
            break;
        case '2' :
            printf("please enter the surname\n");
            cin >> inStr;
            for (int i=0; i <patientCount; i++)
            {
                if (strcmp(patientList[i].surname, inStr) == 0)
                {
                    printf("patient was found:\n");
                    printOnePatient(patientList, patientCount, patientList[i].number);
                    patientFound = true;
                }
            }
            break;
        case '3' :
            printf("please enter the year of birth\n");
            cin >> inStr;
            for (int i=0 ; i <patientCount; i++)
            {
                if (patientList[i].dateOfBirth == (int) atoi(inStr))
                {
                    printf("patient was found:\n");
                    printOnePatient(patientList, patientCount, patientList[i].number);
                    patientFound = true;
                }
            }
            break;
        case '4' :
            printf("please enter the gender\n");
            cin >> inStr;
            for (int i=0 ; i <patientCount; i++)
            {
                if (patientList[i].gender == inStr[0])
                {
                    printf("patient was found:\n");
                    printOnePatient(patientList, patientCount, patientList[i].number);
                    patientFound = true;
                }
            }
            break;
        case '5' :
            printf("please enter the height as integer rounded to floor\n");
            cin >> inStr;
            for (int i=0 ; i <patientCount; i++)
            {
                if (floor(patientList[i].hight) == (int) atoi(inStr))
                {
                    printf("patient was found:\n");
                    printOnePatient(patientList, patientCount, patientList[i].number);
                    patientFound = true;
                }
            }
            break;
        case '6' :
            printf("please enter the weight as integer rounded to floor\n");
            cin >> inStr;
            for (int i=0 ; i <patientCount; i++)
            {
                if (floor(patientList[i].weight) == (int) atoi(inStr))
                {
                    printf("patient was found:\n");
                    printOnePatient(patientList, patientCount, patientList[i].number);
                    patientFound = true;
                }
            }
            break;
        case '7' :
            printf("please enter the mass index as integer rounded to floor\n");
            cin >> inStr;
            for (int i=0 ; i <patientCount; i++)
            {
                if (floor(patientList[i].massIndx) == (int) atoi(inStr))
                {
                    printf("patient was found:\n");
                    printOnePatient(patientList, patientCount, patientList[i].number);
                    patientFound = true;
                }
            }
            break;
        case 'q' :
            patientFound = true;
            break;
        default :
            printf("Wrong choice, please enter valid command\n");
    }

    if (patientFound == false)
    {
        printf("According the search data, the patient was not found");
    }
}

void editPatient(Patient *patientList, int patientCount)
{
    char inStr[30];
    int patientNo, patientIndx;
    bool editIsWorking = true;
    printf("Enter No. of patient you want to edit\n");
    cin >> inStr;
    patientNo = (int) atoi(inStr);
    patientIndx = patientNo -1;
    printOnePatient(patientList, patientCount, patientNo);

    while (editIsWorking != false)
    {
        printf("EDITING MENU OF THE PATIENT NO: %d\n", patientNo);
        printf("\t 1 - edit name\n");
        printf("\t 2 - edit surname\n");
        printf("\t 3 - edit year of birth\n");
        printf("\t 4 - edit gender\n");
        printf("\t 5 - edit height (cm)\n");
        printf("\t 6 - edit weight (kg)\n");
        printf("\t q - quit editing\n");

        cin >> inStr;

        switch (inStr[0]) {
            case '1' :
                printf("name: %s , please enter the name:", patientList[patientIndx].name  );
                cin >> inStr;
                strcpy(patientList[patientIndx].name, inStr);
                break;
            case '2' :
                printf("surname: %s , please enter the surname:", patientList[patientIndx].surname  );
                cin >> inStr;
                strcpy(patientList[patientIndx].surname, inStr);
                break;
            case '3' :
                printf("year of birth: %d , please enter the year of birth:", patientList[patientIndx].dateOfBirth );
                cin >> inStr;
                patientList[patientIndx].dateOfBirth = (int) atoi(inStr) ;
                break;
            case '4' :
                printf("gender: %c , please enter the gender:", patientList[patientIndx].gender );
                cin >> inStr;
                patientList[patientIndx].gender =  inStr[0];
                break;
            case '5' :
                printf("height: %3.2f , please enter the height:", patientList[patientIndx].hight );
                cin >> inStr;
                patientList[patientIndx].hight = (float) atof(inStr);
                patientList[patientIndx].massIndx = 0.0;
                break;
            case '6' :
                printf("weight: %3.2f , please enter the weight:", patientList[patientIndx].weight );
                cin >> inStr;
                patientList[patientIndx].weight = (float) atof(inStr);
                patientList[patientIndx].massIndx = 0.0;
                break;
            case 'q' :
                editIsWorking = false;
                break;
            default :
                printf("Wrong choice, please enter valid command\n");
        }
    }
}

int maxPatientNo(Patient *patientList, int patientCount)
{
    int maxPatientNo = 1;
    for (int i=0; i < patientCount-1; i=i+1)
    {
        if (maxPatientNo < patientList[i].number)
            maxPatientNo = patientList[i].number;
    }
    return maxPatientNo;
}

void insertNewPatient(Patient *patientList, int patientCount)
{
    char inStr[30];
    int patientIndx = patientCount-1;
    patientList[patientIndx].number = (int) (maxPatientNo(patientList, patientCount) + 1) ;
    printf("please enter the name \n");
    cin >> inStr;
    strcpy(patientList[patientIndx].name, inStr);
    printf("please enter the surname \n");
    cin >> inStr;
    strcpy(patientList[patientIndx].surname, inStr);
    printf("please enter the year of birth \n");
    cin >> inStr;
    patientList[patientIndx].dateOfBirth = (int) atoi(inStr) ;
    printf("please enter the gender \n");
    cin >> inStr;
    patientList[patientIndx].gender =  inStr[0];
    printf("please enter the height (cm, e.g.: 186) \n");
    cin >> inStr;
    patientList[patientIndx].hight = (float) atof(inStr);
    printf("please enter the weight (kg, e.g.: 65.5) \n");
    cin >> inStr;
    patientList[patientIndx].weight =  (float) atof(inStr);
    patientList[patientIndx].massIndx =  0.0;
}

void coutMassIndex(Patient *patientList, int patientCount)
{
    char inStr[20];
    int patientNo;
    printf("Please enter No. of the patient\n");
    cin >> inStr;
    patientNo = (int) atoi(inStr);
    patientNo;
    printf("Weight (kg): %3.2f  Height (cm): %3.2f \n", patientList[patientNo-1].weight, patientList[patientNo-1].hight/100);
    patientList[patientNo-1].massIndx = (patientList[patientNo-1].weight)/((patientList[patientNo-1].hight/100)*(patientList[patientNo-1].hight/100));
    printf("Patient No.: %d has mass index: %3.2f\n", patientNo, patientList[patientNo-1].massIndx);
}

int loadPatientCount()
{
    char inStr[30];
    ifstream inFileStream;
    inFileStream.open(".\\PatientList.txt", std::ifstream::in);
    if (!inFileStream.is_open())
        printf("The file can't be open");
    else
    {
        inFileStream >> inStr;
        //printf("File was opened, patientCount: %d\n", atoi(inStr));
    }
    inFileStream.close();
    return (int) atoi(inStr) ;
}

void loadPatientList(Patient *patientList)
{
    int patientCount=0;
    char inStr[65], *endptr;
    float inDbl, inFloat;
    ifstream inFileStream;
    inFileStream.open(".\\PatientList.txt", std::ifstream::in);
    inFileStream >> inStr;
    if (!inFileStream.is_open())
        printf("The file can't be open");
    else {
        //printf("File was opened to read the data of patients\n");
    }
    patientCount = (int) atoi(inStr);

    for(int i = 0; i<patientCount; i++)
    {
        inFileStream >> inStr;
        //ret = strtod(inStr, &endptr);
        patientList[i].number = (int) atoi(inStr) ;
            //printf("number was read: %d\n", patientList[i].number );
        inFileStream >> inStr;
        strcpy(patientList[i].name, inStr);
            //printf("name was read: %s\n", patientList[i].name );
        inFileStream >> inStr;
        strcpy(patientList[i].surname, inStr);
            //printf("pavarde nuskaityta: %s\n", patientList[i].surname );
        inFileStream >> inStr;
        patientList[i].dateOfBirth = (int) atoi(inStr) ;
            //printf("gimimo data nuskaityta: %d\n", patientList[i].dateOfBirth );
        inFileStream >> inStr;
        patientList[i].gender = inStr[0];
            //printf("lytis nuskaityta: %c\n", patientList[i].gender);
        inFileStream >> inStr;
        patientList[i].hight =  (float) strtod (inStr, &endptr);//atof(inStr) ; //strtod (inStr, &endptr)
            //printf("ugis nuskaitytas: %3.2f\n", patientList[i].hight );
        inFileStream >> inStr;
        patientList[i].weight = (float) atof(inStr) ;
            //printf("svoris nuskaitytas: %3.2f\n", patientList[i].weight );
        inFileStream >> inStr;
        patientList[i].massIndx = (float) atof(inStr) ;
            //printf("mases indeksas nuskaitytas %3.2f\n", patientList[i].massIndx);
    }
    printf("Patients' list was loaded from file, patients are printed out\n");     //
    printPatients(patientList, patientCount);               //
    printf("Pring of patients was finished\n\n");             //

    inFileStream.close();
}

void printOnePatient(Patient *patientList, int patientCount, int patientNo)
{
    for (int i = 0; i <patientCount; i++)
    {
        if(patientList[i].number == patientNo)
        {
            printf("Number:\t %d\t|", patientList[i].number);
            printf("Name:\t %s\t|", patientList[i].name);
            printf("Surname:\t %s\t|", patientList[i].surname);
            printf("Date of birth:\t %d\n", patientList[i].dateOfBirth);
            printf("Gender:\t %c\t|", patientList[i].gender);
            printf("Height, cm:\t %3.0f\t|", patientList[i].hight);
            printf("Weight, kg:\t %3.1f\t|", patientList[i].weight);
            if (patientList[i].massIndx == 0.0)
                printf("MASS INDEX IS NOT CALCULATED YET\n");
            else
                printf("Mass index:\t %2.2f\n", patientList[i].massIndx);
        }
    }
}

void printPatients(Patient *patientList, int patientCount)
{
    for (int i = 0; i < patientCount; i++)
    {
        printf("Number:\t %d\t|", patientList[i].number);
        printf("Name:\t\t %s\t|", patientList[i].name);
        printf("Surname:\t %s\t|", patientList[i].surname);
        printf("Date of birth:\t %d\n", patientList[i].dateOfBirth);
        printf("Gender:\t %c\t|", patientList[i].gender);
        printf("Height, cm:\t %3.0f\t|", patientList[i].hight);
        printf("Wheight, kg:\t %3.1f\t|", patientList[i].weight);
        if (patientList[i].massIndx == 0.0)
            printf("MASS INDEX IS NOT CALCULATED YET\n");
        else
            printf("Mass index:\t %2.2f\n", patientList[i].massIndx);
    }
}

void savePatientList(Patient *patientList,  int patientCount)
{
    ofstream outFile;
    outFile.open(".\\PatientList.txt",  ios::out );
    outFile << patientCount << "\n";

    for (int i = 0; i < patientCount; i++)
    {
        outFile << patientList[i].number << "\n";
        outFile << patientList[i].name << "\n";
        outFile << patientList[i].surname << "\n";
        outFile << patientList[i].dateOfBirth << "\n";
        outFile << patientList[i].gender << "\n";
        outFile << patientList[i].hight << "\n";
        outFile << patientList[i].weight << "\n";
        outFile << patientList[i].massIndx << "\n";

    }
    outFile.close();
}
