
//Assigning LDRs
int ldrbotr = A0; //bottom r LDR
int ldrbotl = A3; // bottom l
int ldrtopr = A1; // top r LDR
int ldrtopl = A4; // top l

void setup ()
{
  Serial.begin(9600);
}

void loop()
{
  int topl = analogRead(ldrtopl);
  int topr = analogRead(ldrtopr);
  int botl = analogRead(ldrbotl);
  int botr = analogRead(ldrbotr);

  // calculating average
  int avgtop = (topl + topr) / 2; //average of top LDRs
  int avgbot = (botl + botr) / 2; //average of bottom LDRs
  int avgleft = (topl + botl) / 2; //average of left LDRs
  int avgright = (topr + botr) / 2; //average of right LDRs
  delay(200);
  Serial.print("  Top Left: ");
  Serial.print(topl);

  Serial.print("  Top Right: ");
  Serial.print(topr);

  Serial.print("  Bottom Left: ");
  Serial.print(botl);

  Serial.print("  Bottom Right: ");
  Serial.print(botr);
  Serial.println(" ");


}
