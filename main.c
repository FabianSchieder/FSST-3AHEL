/**
  * @copyright Fabian Schieder
  * @file    main.c
  * @author  Fabian Schieder
  * @version V1.0
  * @date    04.10.2023
  * @brief   Program for creating a student list
  * History:  25.09.2024 created comments
  */

#include <stdio.h>
#include <stdlib.h>

/**
  * @brief Struct for a student
  */
struct Student
{
    int number;             // Student number
    char firstName[20];      // First name of the student
    char lastName[20];       // Last name of the student
};

/**
 * Function Prototypes
 */
int printMenu();
struct Student* addStudents(struct Student* students, int* size);
void printStudents(struct Student* students, size_t size);
struct Student* getStudentsFile(int* size);
void writeStudentsFile(struct Student* students, size_t size);

/**
  * @brief   Main function
  * @retval  Exit code
  *          EXIT_SUCCESS on success
  */
int main(void)
{
    int option = 0;                 // Menu option selected by user
    int size = 0;                   // Current number of students
    struct Student* students = NULL; // Pointer to the dynamic array of students

    do
    {
        option = printMenu();        // Display menu and get option

        if (option == -1)
        {
            printf("\nBitte geben Sie eine gueltige Zahl ein.\n\n");
        }
        else
        {
            switch(option)
            {
                case 1:
                    students = addStudents(students, &size); // Add new students
                    break;

                case 2:
                    printStudents(students, size);           // Print student list
                    break;

                case 3:
                    students = getStudentsFile(&size);       // Load students from file
                    break;

                case 4:
                    writeStudentsFile(students, size);       // Save students to file
                    break;

                case 0:
                    printf("Programm beendet.\n");      // Exit when option is 0
                    break;

                default:
                    printf("Fehlerhafte Eingabe: ");       // invalid option
                    break;
            }
        }
    } while(option != 0);                                // Continue until user selects "exit"

    free(students);                                      // Free dynamically allocated memory

    return EXIT_SUCCESS;                                 // Return success code
}

/**
  * @brief   Function to print the menu options
  * @retval  Selected menu option
  */
int printMenu(void)
{
    int option;
    printf("Menu:\n");
    printf("0. Beenden\n");
    printf("1. Eingabe von Schuelern\n");
    printf("2. Ausgabe von Schuelern\n");
    printf("3. Lesen der Schueler von einem File\n");
    printf("4. Schreiben der Schueler auf ein File\n");
    printf("\nEingabe: ");

    if (scanf("%d", &option) != 1)
    {

        while(getchar() != '\n');       // discard chars until \n
        return -1;
    }

    return option;
}

/**
  * @brief   Function to add students
  * @param   students Pointer to current array of students
  * @param   size     Pointer to the number of students
  * @retval  Updated pointer to the array of students
  */
struct Student* addStudents(struct Student* students, int* size)
{
    int newStudentsCount = 0;                            // Number of new students to add
    int newSize = 0;                                     // New total size of student array

    printf("\rWieviele Schueler wollen Sie hinzufuegen?\n\rEingabe: ");
    scanf("%i", &newStudentsCount);                      // Get the number of new students

    newSize = *size + newStudentsCount;                  // Calculate new size of array
    students = realloc(students, newSize * sizeof(struct Student)); // Resize array

    for(int i = *size; i < newSize; i++)                 // Loop to add new students
    {
        students[i].number = i + 1;                      // Assign student number
        printf("\rVorname (Schueler %i): ", i + 1);      // Prompt for first name
        scanf("%s", students[i].firstName);
        printf("\rNachname (Schueler %i): ", i + 1);     // Prompt for last name
        scanf("%s", students[i].lastName);
    }

    *size = newSize;                                     // Update size of the student array
    return students;                                     // Return updated array
}

/**
  * @brief   Function to print all students
  * @param   students Pointer to array of students
  * @param   size     Number of students in the array
  * @retval  None
  */
void printStudents(struct Student* students, size_t size)
{
    if(size == 0)
    {
        printf("\rEs sind keine Schueler gespeichert! \n");                               // Print error message
        return;
    }

    if(students == NULL)                                 // Check if student array is null
    {
        printf("\rFehler beim Ausgeben der Schueler! \n");                               // Print error message
        return;
    }

    for(int i = 0; i < size; i++)                        // Loop through all students
    {
        printf("\rSchueler %i: Nummer: %d, Vorname: %s, Nachname: %s\n", i + 1, students[i].number, students[i].firstName, students[i].lastName);
    }
}

/**
  * @brief   Function to load students from a file
  * @param   size Pointer to store the number of students
  * @retval  Pointer to array of students, or NULL on error
  */
struct Student* getStudentsFile(int* size)
{
    char filename[256];                                  // Buffer to store file name
    int count = 0;                                       // Counter for students read from file

    printf("\n\rPfad: ");
    scanf("%s", filename);                               // Get file path from user

    FILE* file = fopen(filename, "r");                   // Open file for reading
    if (file == NULL)                                    // Check if file was opened successfully
    {
        printf("\n\rFehler beim Oeffnen der Datei!\n");      // Print error message
        return NULL;
    }

    struct Student* students = NULL;                     // Pointer to array of students
    struct Student temp;                                 // Temporary variable for reading students

    while (fscanf(file, "%d %19s %19s", &temp.number, temp.firstName, temp.lastName) == 3)
    {
        count++;                                         // Increment student count
        students = realloc(students, count * sizeof(struct Student)); // Resize student array
        if (students == NULL)                            // Check for memory allocation failure
        {
            printf("Fehler beim Zuweisen von Speicher!\n");
            fclose(file);                                // Close file
            return NULL;
        }
        students[count - 1] = temp;                      // Copy student data to array
    }

    if(count == 0)
    {
        printf("\n\rDatei ist leer!\n");
    }
    else
    {
        printf("\rDatei erfolgreich eingelesen! \n");
    }

    *size = count;                                       // Update size with number of students read
    fclose(file);                                        // Close file
    return students;                                     // Return array of students
}

/**
  * @brief   Function to save students to a file
  * @param   students Pointer to array of students
  * @param   size     Number of students in the array
  * @retval  None
  */
void writeStudentsFile(struct Student* students, size_t size)
{
    char filename[256];                                  // Buffer to store file name
    printf("\n\rPfad: ");
    scanf("%s", filename);                               // Get file path from user

    FILE* file = fopen(filename, "w");                   // Open file for writing

    if (file == NULL)                                    // Check if file was opened successfully
    {
        printf("\n\rFehler beim Oeffnen der Datei zum Schreiben.\n");
        return;
    }

    for (size_t i = 0; i < size; i++)                    // Loop through all students
    {
        fprintf(file, "%d %s %s\n", students[i].number, students[i].firstName, students[i].lastName); // Write each student to file
    }

    fclose(file);                                        // Close file
    printf("\n\rSchuelerdaten wurden erfolgreich in die Datei geschrieben.\n");
}
/**
 * @brief Test123
 */

