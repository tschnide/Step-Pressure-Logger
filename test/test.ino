
#include <SPI.h>
#include <SD.h>

//  Sensor initializations
File finalFile;
File fileA;
File fileB;
File fileC;

void setup()
{
    Serial.begin(9600);

    //  Listens for off button to break the code loop
    pinMode(6, INPUT);
    //  Onboard led gets set to ouput
    pinMode(LED_BUILTIN, OUTPUT);

    //  Check SD
    Serial.print("Initializing SD card...");
    //  Pin 10 is the slave select this verifies that the sd module is working
    if (!SD.begin(10)) {
        Serial.println("Initialization failed!");
        return;
    }
    Serial.println("Initialization done.");

    //  This is meant to operate with bluetooth in the future. Writing to files is very similar to sending 
    //  data over bluetooth so this code is a working placeholder.
    SD.remove("final.csv");
    SD.remove("fileA.csv");
    SD.remove("fileB.csv");
    SD.remove("fileC.csv");
    finalFile = SD.open("final.csv", FILE_WRITE);
    fileA = SD.open("fileA.csv", FILE_WRITE);
    fileB = SD.open("fileB.csv", FILE_WRITE);
    fileC = SD.open("fileC.csv", FILE_WRITE);

   /*******************************************************   
   *Read from the sensors until the off button is pressed
   *******************************************************/
    if (finalFile) {
        while (digitalRead(6) == 0) {
            if (analogRead(A6)) {
                fileA.print(analogRead(A6));
                fileA.print(",");
            }
            if (analogRead(A5)) {
                fileB.print(analogRead(A5));
                fileB.print(",");
            }
            if (analogRead(A4)) {
                fileC.print(analogRead(A4));
                fileC.print(",");
            }
        }
        // close the file:
        Serial.println("button pressed");
        fileA.close();
        fileB.close();
        fileC.close();
    }
    else {
        // if the file didn't open, print an error:
        Serial.println("error in block 1");
    }

    /*******************************************************   
   * Read the file for verification
   *******************************************************/
    fileA = SD.open("fileA.csv");
    fileB = SD.open("fileB.csv");
    fileC = SD.open("fileC.csv");
    if (fileA && fileB && fileC) {

        Serial.println("File Contents: \n");

        // read from the file until there's nothing else in it:
        Serial.write("File A \n");
        while (fileA.available()) {
            Serial.write(fileA.read());
        }
        Serial.write("\nFile B \n");
        while (fileB.available()) {
            Serial.write(fileB.read());
        }
        Serial.write("\nFile C \n");
        while (fileC.available() != 0) {
            Serial.write(fileC.read());
        }
    }
    else {
        // if the file didn't open, print an error:
        Serial.println("error in block 2");
    }
    // close the files:
    fileA.close();
    fileB.close();
    fileC.close();

    /*******************************************************   
   * Final file creation
   * Combines fileA, fileB, fileC, into finalFile to be easily exported
   * This can be replaced by streaming the three sensors through bluetooth rather than writing to files
   *******************************************************/
    finalFile = SD.open("final.csv", FILE_WRITE);
    fileA = SD.open("fileA.csv");
    fileB = SD.open("fileB.csv");
    fileC = SD.open("fileC.csv");

    if (finalFile && fileA && fileB && fileC) {
        Serial.println("\nCreating final file");

        while (fileA.available()) {
            finalFile.write(fileA.read());
        }
        finalFile.write("\n");
        Serial.println("A written");

        while (fileB.available()) {
            finalFile.write(fileB.read());
        }
        finalFile.write("\n");
        Serial.println("B written");

        while (fileC.available()) {
            finalFile.write(fileC.read());
        }
        finalFile.write("\n");
        Serial.println("C written");
    }
    else {
        Serial.println("Error in block 3");
    }
    finalFile.close();

   /*******************************************************   
   * Read the file for verification
   * This output is useful for testing
   *******************************************************/
//    finalFile = SD.open("final.csv");
//
//    if (finalFile) {
//        Serial.println("File Contents: ");
//
//        // read from the file until there's nothing else in it:
//        while (finalFile.available() != 0) {
//            Serial.write(finalFile.read());
//        }
//        // close the file:
//        finalFile.close();
//    }
//    else {
//        // if the file didn't open, print an error:
//        Serial.println("The contents of finalFile.csv could not be displayed.");
//    }
}

void loop()
{
    // Nothing happens here
}
