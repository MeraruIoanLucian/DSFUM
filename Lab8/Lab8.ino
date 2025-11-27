#include <SPI.h>
#include <SD.h>

FILE root;
String opt = "ls";
bool hasRun = false;
String caleCurenta = "/";

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // va asteptam sa deschideti consola seriala
  }
  if (!SD.begin(10)) { // 4 este pinul SS al cardului SD
    Serial.println("Nu putem accesa cardul... aveti un card acolo ? este formatat FAT16 sau FAT32 ?");    
    return; // iese si nu mai face nimic
  }  
  Serial.println("Accesare card -> OK");
  root = SD.open("/");
}

void loop()
{
  if (opt == "ls")
  {
    Serial.println("Listing files");
    printDirectory(root, 0);
    Serial.println("Stopped listing files");
    hasRun = true;
  }
  else if (opt.startswith("cd "))
  {
    String folderNou = opt.subString(3);
    executeCd(folderNou);
  }
}

void printDirectory(File dir, int numTabs)
{
  while(true)
  {
    File entry = dir.OpenNextFile();
    if(!entry)
    {
      dir.rewindDirectory();
      break;
    }
  

    for(uint8_t i = 0; i<numTabs; i++)
    {
     Serial.print('\t');
    }

    Serial.print(entry.name());

    if(entry.isDirectory())
    {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    }
    else
    {
      Serial.print('\t\t');
      Serial.println(entry.size(), DEC);
    }

  entry.close();
  }

}
void executeCd(String folder)
{
  if(folder == "..")
  {
    if(caleCurenta == "/")
    {
      Serial.println("esti deja in root");
      return;
    }
    int ultimulSlash = caleCurenta.lastIndexOf("/");
    if(ultimulSlash == 0)
    {
      caleCurenta = "/";
    }
    else
    {
      caleCurenta = caleCurenta.substring(0, ultimulSlash);
    }
    return;
  }

  String caleTest;
  if(caleCurenta == '/')
  {
    caleTest = "/" + folder;
  }
  else
  {
    caleTest = caleCurenta + "/" + folder;
  }

  if(SD.exists(caleTest))
  {
    File f = SD.open(caleTest);
    if(f.isDirectory())
    {
      caleCurenta = caleTest;
    }
    else
    {
      Serial.println("Eroare " + folder + " e folder");
    }
  }
}