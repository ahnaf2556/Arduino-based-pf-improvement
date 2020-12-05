#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,10,9,8,7);



const int pin=13;

int caps[]={0,1,2,3,4,5,6};

const double pi=acos(-1.0);

const int freq=50;

double pf;



void setup() {
  // put your setup code here, to run once:

  pinMode(pin,INPUT);
  
  pf=0.0;
  int i=0;
  for(i=0;i<7;i++)pinMode(caps[i],OUTPUT);

  lcd.begin(16,2);

}

void loop() {
  // put your main code here, to run repeatedly:

  //double pf;

  pf=calc();
  PRINT(abs(pf));

  double max_pf=abs(pf);
  int pos=0;

  int i=0;
  while(abs(pf)<0.95)
  {
    digitalWrite(caps[i],HIGH);
    delay(10);
    pf=calc();
    if(abs(pf)>max_pf)
    {
      max_pf=abs(pf);
      pos=i;
    }
    i++;
    if(i==7)break;
  }

  i--;

  while(i>pos)
  {
    digitalWrite(caps[i],LOW);i--;
  }

  
  

  pf=calc();
  PRINT(abs(pf));

  
}


double calc()
{
  double prev_pf=pf;
  //delay(10);
  double t = pulseIn(pin,HIGH);
  t = t/pow(10,6);
  pf = cos(2*PI*freq*t);
  if(pf<0)pf=pf-0.01;
  if(pf>0)pf=pf+0.01;
  if(pf>1.00)pf=1.00;
  if(abs(abs(pf)-1.00)<0.000001)pf=prev_pf;
  if(abs(abs(pf)-0.0)<0.000001)pf=calc();
  delay(10);
  return pf;
}

void PRINT(double p)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("pf = ");
  lcd.print(p,3);
  delay(20);
}
