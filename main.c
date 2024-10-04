/**
  * @copyright Fabian Schieder
  * @file    main.c
  * @author  Fabian Schieder
  * @version V1.0
  * @date    04.10.2023
  * @brief   Program for creating a class list
  * @note
  *
  * History:  25.09.2024 created comments
  */

#include <stdio.h>
#include <stdlib.h>

/**
 * Struct for a student
 */

struct Student
{
    int number;
    char firstName[20];
    char lastName[20];
};

/**
 * Function Prototypes
 */

int printMenu();
struct Student* addStudents(struct Student* students, int* size);
void printStudents(struct Student* students, size_t size);
struct Student* getStudentsFile(int* size);
void writeStudentsFile(struct Student* students, size_t size);

int main(void)
{
    int option = 0;
    int size = 0;
    struct Student* students = NULL;

    do
    {
        option = printMenu();

        switch(option)
        {
            case 1:
                students = addStudents(students, &size);
                break;

            case 2:
                printStudents(students, size);
                break;

            case 3:
                students = getStudentsFile(&size);
                break;

            case 4:
                writeStudentsFile(students, size);
                break;

            default:
                break;
        }
    } while(option != 0);

    free(students);

    return EXIT_SUCCESS;
}


/**
  * @brief Function to print the menu
  * @retval     error code:
  *             SUCCESS
  *             ERR_NULLPTR
  */

int printMenu()
{
    int option = 0;

    printf("\n0. Beenden\n1. Eingabe von Schuelern\n2. Ausgabe von Schuelern\n3. Lesen der Schueler von einem File\n4. Schreiben von Schuelern auf ein File\n\nEingabe: ");
    scanf(" %i", &option);

    return option;
}

/**
  * @brief Function to add a student
  * @retval     error code:
  *             SUCCESS
  *             ERR_NULLPTR
  */

struct Student* addStudents(struct Student* students, int* size)
{
    int newStudentsCount = 0;
    int newSize = 0;

    printf("\rWieviele Schueler wollen Sie hinzufuegen?\n\rEingabe: ");
    scanf("%i", &newStudentsCount);

    newSize = *size + newStudentsCount;
    students = realloc(students, newSize * sizeof(struct Student));

    for(int i = *size; i < newSize; i++)
    {
        students[i].number = i + 1;
        printf("\rVorname (Schueler %i): ", i + 1);
        scanf("%s", students[i].firstName);
        printf("\rNachname (Schueler %i): ", i + 1);
        scanf("%s", students[i].lastName);
    }

    *size = newSize;
    return students;
}

/**
  * @brief function to output the students
  * @retval     error code:
  *             SUCCESS
  *             ERR_NULLPTR
  */

void printStudents(struct Student* students, size_t size)
{
    for(int i = 0; i < size; i++)
    {
        printf("Schueler %i: Nummer: %d, Vorname: %s, Nachname: %s\n", i + 1, students[i].number, students[i].firstName, students[i].lastName);
    }
}

/**
  * @brief function to read students from a file
  * @retval     error code:
  *             SUCCESS
  *             ERR_NULLPTR
  */

struct Student* getStudentsFile(int* size)
{
    char filename[256];
    int count = 0;

    printf("Pfad: ");
    scanf("%s", filename);

    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Fehler beim Oeffnen der Datei.\n");
        return NULL;
    }

    struct Student* students = NULL;
    struct Student temp;


    while (fscanf(file, "%d %19s %19s", &temp.number, temp.firstName, temp.lastName) == 3)
    {
        count++;
        students = realloc(students, count * sizeof(struct Student));
        if (students == NULL)
        {
            printf("Fehler beim Zuweisen von Speicher.\n");
            fclose(file);
            return NULL;
        }
        students[count - 1] = temp;
    }

    *size = count;
    fclose(file);
    return students;
}

/**
  * @brief function to write students in a file
  * @retval     error code:
  *             SUCCESS
  *             ERR_NULLPTR
  */

void writeStudentsFile(struct Student* students, size_t size)
{
    char filename[256];
    printf("Pfad: ");
    scanf("%s", filename);

    FILE* file = fopen(filename, "w");

    if (file == NULL)
    {
        printf("Fehler beim Oeffnen der Datei zum Schreiben.\n");
        return;
    }

    for (size_t i = 0; i < size; i++)
    {
        fprintf(file, "%d %s %s\n", students[i].number, students[i].firstName, students[i].lastName);
    }

    fclose(file);
    printf("Schuelerdaten wurden erfolgreich in die Datei geschrieben.\n");
}