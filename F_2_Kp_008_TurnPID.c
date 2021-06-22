
////#include <stdio.h>  // If a library is standard C library use the <> braces
////#include <stdlib.h>
////#include <stdint.h>
////#include <string.h>
////#include <limits.h>
////#include "UART.h"
////#include "PLL.h"
////#include "PWM.h"
////#include "SysTick.h"
////#include "Timer0.h"
////#include "Timer1.h"
////#include "Timer2.h"
////#include "tm4c123gh6pm.h"


////unsigned long distance0=0, distance1=0, distance2=0;
////unsigned long count0=0, count1=0, count2=0;
////unsigned char stp_intr=0, blink_intr=0;
////unsigned long one_second_count = 0;

////long StartCritical (void);    // previous I bit, disable interrupts
////void EndCritical(long sr);    // restore I bit to previous value

////void WaitForInterrupt(void);
////void DisableInterrupts(void); 
////void EnableInterrupts(void);
////void PortF_Init(void);
////void PortE_Init(void);
////void PortA_Init(void);
////void PortB_Init(void);
////void PortC_Init(void);
////void PortD_Init(void);
////void timer0FrontDistance0(unsigned long *distance0);
////void timer1RightDistance1_1(unsigned long *distance1);
////void timer2LeftDistance2_2(unsigned long *distance2); 
////void stop(void);
////void shiftLeft(void);
////void shiftRight(void);
////void moveStraight(void);
////void stepBack(void);
////void forwardMove(void);
////void rightMove(void);
////void leftMove(void);
////void motorA(unsigned long speedA);
////void motorB(unsigned long speedB);

////void GPIOPortF_Handler(void){ 
////	if (GPIO_PORTF_RIS_R&0x01){
////		GPIO_PORTF_ICR_R = 0x01; //acknldge intr sw2
////		if (stp_intr==3)
////			stp_intr = 1;
////		else
////		  stp_intr++;
////	}
////	else if (GPIO_PORTF_RIS_R&0x10){
////		GPIO_PORTF_ICR_R = 0x10; //acknldge intr sw1
////		if (blink_intr>0)
////			blink_intr = 0;
////		blink_intr++;
////	}
////}

////void UserTask(void){		//Timer0  
////	if (GPIO_PORTE_DATA_R&0x10) //PE4 as input
////		count0 = count0 + 1;
////}

////void UserTask1(void){		//Timer1
////	if (GPIO_PORTD_DATA_R&0x04) //PD2 as input
////		count1 = count1 + 1;
////}

////void UserTask2(void){		//Timer2
////	if (GPIO_PORTE_DATA_R&0x04)  //PE2 as input
////		count2 = count2 + 1;
////}
////void OutCRLF(void){
////  UART_OutChar(CR);
////  UART_OutChar(LF);
////}
////void F_R_L_Sensor(void) {
////		//Timer0 Port PE4-5, distance0	
////		timer0FrontDistance0(&distance0);				
////		//Timer1 Port PD2-3, distance1, 1
////		timer1RightDistance1_1(&distance1);	
////		//Timer2 Port PE2-3, distance2, 2
////		timer2LeftDistance2_2(&distance2); 
////}

////int main (void) {	
////	unsigned long index = 0, i = 0, ii = 0;
////	unsigned long pDistn0=0, count = 0;
////	unsigned char goTurn = 0, out=0, error=0;
////	unsigned char turnLeft = 0, turnRight = 0;
////	unsigned char r=0, l=0, f=0, setPoint=0;
////	unsigned char DFS_1stRun;
////	unsigned char turn = 0, deadEnd=0, goal=0;
////	unsigned char arrayTurns[4] = {0, 0, 0, 0};	
////	unsigned char travalArray[250]; 
////	unsigned char secndRunArray[250];
////	unsigned long speedA=10000, speedB=10000;
////	signed long Ep=0, Ed=0, Ei=0, lastError=0;
////	double Kp=0.1, Ki=0, Kd=0.1;
////	unsigned long loopCount=0;
////	
////	DisableInterrupts(); 
////  PLL_Init();  // bus clock at 80 MHz
////	PortF_Init();
////	PortE_Init();
////	PortA_Init();
////	PortB_Init();
////	PortC_Init();
////	PortD_Init();
////	SysTick_Init(); 
////	UART_Init();  																
////																
////	Timer0_Init(&UserTask,80);   // 1us interrupt
////	Timer1_Init(&UserTask1,80);  // 1us interrupt
////	Timer2_Init(&UserTask2,80);  // 1us interrupt
////	EnableInterrupts();															
////																
////	PWM0A_Init(40000,15000);     // initi8alize PWM0, 1000 Hz
////	PWM0B_Init(40000,15000);     // initialize PWM0, 1000 Hz, 50% duty
////	
////  GPIO_PORTF_DATA_R = 0x04;		 // Blue led																
////	GPIO_PORTB_DATA_R |= 0x01; 	 // MotorA foward	
////	GPIO_PORTB_DATA_R |= 0x02;   // MotorB foward
////	PWM0A_Duty(10000);   			   //40,000 == 100% , 100
////	PWM0B_Duty(15000);		       //40,000 == 100% , 3000  	
////  GPIO_PORTF_DATA_R = 0x04;		 // Blue led

////	for (unsigned char t=0; t<250; t++)
////		travalArray[t] = 0;
////	for (unsigned char s=0; s<250; s++)
////	  secndRunArray[s] = 0;
////		
////	F_R_L_Sensor();
////	F_R_L_Sensor();

////	while(distance0<150) {
////		stop();
////		F_R_L_Sensor();
////	}
////	OutCRLF();  OutCRLF();
////	UART_OutString("filter distance0---");
////	OutCRLF();
////	
////////initially, turn = 0, turn!='U';	
////	while ((goal == 0)||(goal == 2)) {
////		if(goal==2) {
////			GPIO_PORTF_DATA_R = 0x00;
////			count = 0;
////			while(count<10) {
////				GPIO_PORTF_DATA_R ^= 0x04;	//led blue blinking
////				SysTick_Wait10ms(30);
////				count++;
////			}
////			count = 0;
////			turn = 0;
////			GPIO_PORTB_DATA_R |= 0x01; 	 // MotorA foward	
////			GPIO_PORTB_DATA_R |= 0x02;   // MotorB foward
////			PWM0A_Duty(2500);   			   //40,000 == 100% , 100
////			PWM0B_Duty(10000);		       //40,000 == 100% , 3000
////		}
////		while (turn != 'U') {	
////			while (turn == 0){ 
////				F_R_L_Sensor();	

////				//***turn RF == 0x03 cyane
////				if ((distance0>120)&&(distance0<400)
////						&&(distance1>150)&&(distance1<400)
////						&&(distance2>30)&&(distance2<60)
////						&&(distance1>distance2)
////						&&(r==0)&&(f==0)) {
////					stop(); 
////					GPIO_PORTF_DATA_R = 0x0C;						
////						
////				  count=0; out = 0; 
////				 	while((count<10)) {
////						GPIO_PORTF_DATA_R ^= 0x0C;//cyane blinking
////						SysTick_Wait10ms(20);
////					  count++;
////					}
////					count=0;
////					
////					F_R_L_Sensor();
////					if (distance1<150)
////						out = 1;					
////				  if((turn == 0)&&(goal==0)&&(out==0)){
////						turn = 0x03;
////				  }
////				  else if((turn==0)&&(goal==2)&&(out==0)){
////						ii++;
////					  if (secndRunArray[ii]==82)
////							r = 1;
////					  else if (secndRunArray[ii]==70)
////					    f = 1;
////					  OutCRLF();
////				  }		
////          if (out == 1) {
////						count=0;
////						while(count<20) {
////							GPIO_PORTF_DATA_R ^= 0x04;
////							SysTick_Wait10ms(10);
////							count++;
////						}
////						count=0;						
////          }	
////          out = 0; turnLeft=0; turnRight=0;				
////				}
////				//***turn LF ==0x05	green		
////				else if ((distance0>120)&&(distance0<400)
////								 &&(distance1>30)&&(distance1<60)
////								 &&(distance2>150)&&(distance2<400)
////								 &&(distance1<distance2)
////								 &&(l==0)&&(f==0)) {			 
////					stop(); 
////				  GPIO_PORTF_DATA_R = 0x08;//green blinking
////									 
////				  count=0; out = 0;
////				  while((count<10)) {
////						GPIO_PORTF_DATA_R ^= 0x08;
////						SysTick_Wait10ms(20);
////						count++;
////				  }
////				  count=0; 
////					
////					F_R_L_Sensor();						
////					if (distance2<150)
////						out = 1;			 
////				  if((turn == 0)&&(goal==0)&&(out==0)){
////					  turn = 0x05;	
////				  }
////				  else if((turn==0)&&(goal==2)&&(out==0)){
////					  ii++;
////					  if (secndRunArray[ii]==70){
////						  f = 1;
////					  }
////						else if (secndRunArray[ii]==76) {
////							l = 1;
////						}
////					}  
////          if (out == 1) {
////						count=0;
////						while(count<20) {
////							GPIO_PORTF_DATA_R ^= 0x04;
////							SysTick_Wait10ms(10);
////							count++;
////						}
////						count=0;						
////          }	
////          out = 0;	turnLeft=0; turnRight=0;				
////				}
////				//***turn LR == 0x06 yellow
////				else if ((distance0>20)&&(distance0<80)
////								 &&(distance1>100)&&(distance1<300) 
////								 &&(distance2>100)&&(distance2<300)
////								 &&(r==0)&&(l==0)) {											
////					stop();				 
////					GPIO_PORTF_DATA_R = 0x0A;//yellow blinking
////									 
////				  count=0;
////				  while(count<10) {
////						GPIO_PORTF_DATA_R ^= 0x0A;//yellow blinking
////						SysTick_Wait10ms(20);
////						count++;
////				  }
////				  count=0; out = 0;
////					
////          stop();
////					F_R_L_Sensor();						
////					if ((distance1<100)||(distance2<100)
////						  ||(distance0>80))
////						out = 1;														 
////					if((turn == 0)&&(goal==0)&&(out==0)){
////						turn = 0x06;
////            if ((turnLeft==3)||(turnRight==3)){
////							goal = 1;
////						  turn = 'U';
////            }							
////					}
////					else if((turn==0)&&(goal==2)&&(out==0)){
////						ii++;
////						if (secndRunArray[ii]==82){
////							r = 1;
////						}
////						else if(secndRunArray[ii]==76) {
////							l = 1;
////						}
////						OutCRLF();
////						if ((turnLeft==3)||(turnRight==3)) {
////							goal = 3;
////							turn = 'U';
////						}
////					}		
////          if (out == 1) {
////						count=0;
////						while(count<20) {
////							GPIO_PORTF_DATA_R ^= 0x04;
////							SysTick_Wait10ms(10);
////							count++;
////						}
////						count=0;						
////          }	
////          out = 0; turnLeft=0; turnRight=0;				
////				}
////				//STOP
////				else if ((distance0>20)&&(distance0<80)
////								 &&(distance1>20)&&(distance2>20)
////								 &&(distance1<50)&&(distance2<50)){					 
////					stop();	stp_intr = 0;	goTurn = 0;
////					GPIO_PORTF_DATA_R = 0x02;					 
////					
////					count = 0; out = 0;
////					while ((count<10)&&(out==0)) {
////						F_R_L_Sensor();
////						GPIO_PORTF_DATA_R ^= 0x02; //led red
////						SysTick_Wait10ms(10);
////						count++;	
////						if (distance0 <50) {
////							out = 1;
////						}
////					}
////					count = 0;	out = 0;
////					if ((distance0>50)&&(distance1<60)
////						  &&(distance2<60)) {
////						turn = 0;
////						goTurn = 0;
////					}
////					else if((distance0<50)&&(distance1<50)
////						      &&(distance2<50)&&(stp_intr==0)) {
////						goTurn = 1;
////						deadEnd = 1;
////						turn = 0;					    		  
////					}
////					stp_intr = 0;	
////					
////					if(goTurn==1) {
////						GPIO_PORTF_DATA_R = 0x02;	
////						SysTick_Wait10ms(100);					
////						//U-Turn						
////						GPIO_PORTB_DATA_R |= 0x01; 	  //MotorA, backward	
////						GPIO_PORTB_DATA_R &= ~0x02;  	//MotorB, foward
////						PWM0A_Duty(100);   					  //40,000 == 100%		
////						PWM0B_Duty(39000);		        //40,000 == 100%	
////						SysTick_Wait10ms(40);    		  //turn for 1 second						
////						stop();
////						//END of U-turn							
////            SysTick_Wait10ms(100);  //wait
////						
////						moveStraight();
////						SysTick_Wait10ms(10);
////						stop(); goTurn = 0;				
////					}
////					turnLeft=0; turnRight=0;
////				}								 

////				//turn RIGTH
////				else if(((distance0>30)&&(distance0<80)
////								&&(distance1>100)&&(distance1<500)
////								&&(distance2>20)&&(distance2<60)
////								&&(distance1>distance2))
////								||(r == 1)){//RIGHT TURN																	         
////					stop();	
////					GPIO_PORTF_DATA_R = 0x0E;	
////									
////          count = 0;									
////					while((count<10)&&(r==0)){
////						F_R_L_Sensor();
////						SysTick_Wait10ms(1); 
////						if (r==1)
////							GPIO_PORTF_DATA_R ^= 0x0E;	
////						else if (r==0)
////							GPIO_PORTF_DATA_R = 0x0E;	
////						count++;
////					}
////					count = 0;
////					
////					goTurn = 0;
////					if (((distance0<80)&&(distance1>100))||(r==1)) {
////						goTurn = 1;
////					}
////					if (goTurn==1) {				
////						SysTick_Wait10ms(200);  //wait
////						//one time turn RIGHT
////						GPIO_PORTB_DATA_R &= ~0x01; //MotorA, backward	
////						GPIO_PORTB_DATA_R |= 0x02;  //MotorB, foward
////						PWM0A_Duty(39000);   			  //40,000 == 100%		
////						PWM0B_Duty(500);		        //40,000 == 100%
////						SysTick_Wait10ms(20);    							
////						stop();	
////						SysTick_Wait10ms(200);     //wait
////            turnLeft=0; turnRight++;						
////						//END turn Right		
////					}
////					goTurn = 0;
////					
////          count = 0;	out = 0;
////          F_R_L_Sensor();					
////					while((count<90)&&(out==0)){						
////						if ((distance1>100)&&(distance2<100)){
////							if((distance0>50)&&(distance2<50)){
////								GPIO_PORTF_DATA_R = 0x0C;
////								rightMove();
////								SysTick_Wait10ms(2);    //2
////								forwardMove();
////								SysTick_Wait10ms(4);	  //3
////								leftMove();
////								SysTick_Wait10ms(2);    //2
////								stepBack();
////								SysTick_Wait10ms(1);		//1		
////								stop();											 
////								F_R_L_Sensor();								
////							}
////							else if ((distance0>50)&&(distance2>50)){	 
////								GPIO_PORTF_DATA_R = 0x0A;											 
////								leftMove();
////								SysTick_Wait10ms(3);   //2
////								forwardMove();
////								SysTick_Wait10ms(4);	 //3
////								rightMove();
////								SysTick_Wait10ms(2);   //1  
////								stepBack();
////								SysTick_Wait10ms(1);	 //1											
////								stop();											 
////								F_R_L_Sensor();	
////							}
////						}	
////            else if ((distance0>50)&&(distance1<100)
////							       &&(distance2<100)) {
////							GPIO_PORTF_DATA_R = 0x0E;								
////							moveStraight();
////							SysTick_Wait10ms(1);
////							stop();
////            }							
////            else if ((distance2>100)&&(distance1<80)) {
////              if ((distance0>50)&&(distance1>50)) {
////								GPIO_PORTF_DATA_R = 0x0C;
////								rightMove();
////								SysTick_Wait10ms(2);    //2
////								forwardMove();
////								SysTick_Wait10ms(4);	  //3
////								leftMove();
////								SysTick_Wait10ms(2);    //2
////								stepBack();
////								SysTick_Wait10ms(1);		//1		
////								stop();											 
////								F_R_L_Sensor();
////              }		
////							else if ((distance0>50)&&(distance1<50)){	
////								GPIO_PORTF_DATA_R = 0x0A;											 
////								leftMove();
////								SysTick_Wait10ms(3);   //2
////								forwardMove();
////								SysTick_Wait10ms(4);	 //3
////								rightMove();
////								SysTick_Wait10ms(2);   //1  
////								stepBack();
////								SysTick_Wait10ms(1);	 //1											
////								stop();											 
////								F_R_L_Sensor();	
////						  }							
////            }
////						else if ((distance0>50)&&(distance1>100)
////							       &&(distance2>100)) {
////							rightMove();
////							SysTick_Wait10ms(2);    //2
////							forwardMove();
////							SysTick_Wait10ms(4);	  //3
////							leftMove();
////							SysTick_Wait10ms(2);    //2
////							stepBack();
////							SysTick_Wait10ms(1);		//1		
////							stop();		
////							leftMove();
////							SysTick_Wait10ms(3);   //2
////							forwardMove();
////							SysTick_Wait10ms(4);	 //3
////							rightMove();
////							SysTick_Wait10ms(2);   //1  
////							stepBack();
////							SysTick_Wait10ms(1);	 //1											
////							stop();																
////						}
////						F_R_L_Sensor();
////						count++;
////					}
////					stop();
////					count = 0; out = 0; stop();
////					SysTick_Wait10ms(200);     //wait	
////					turn = 0; r = 0;
////				}//END turnRIGTH	

////				//turn LEFT
////				else if (((distance0>30)&&(distance0<80)
////								 &&(distance1>20)&&(distance1<60)
////								 &&(distance2>100)&&(distance2<500)
////								 &&(distance2>distance1))
////								 ||(l == 1)){//LEFT TURN										 
////          stop();		 
////					GPIO_PORTF_DATA_R = 0x06;							
////					 
////					count = 0;
////					while(count<10){
////						SysTick_Wait10ms(1); 
////						if (l==1)
////							GPIO_PORTF_DATA_R ^= 0x06;	
////						else if (l==0)
////							GPIO_PORTF_DATA_R = 0x06;	
////						count++;
////					}
////					count = 0;
////					
////					SysTick_Wait10ms(200);     //wait	
////					//one time turn LEFT
////					GPIO_PORTB_DATA_R |= 0x01; //MotorA, forward
////					GPIO_PORTB_DATA_R &= ~0x02;//MotorB, backward
////					PWM0A_Duty(500);   			   //40,000 == 100%		
////					PWM0B_Duty(39000);		     //40,000 == 100%
////					SysTick_Wait10ms(20);    							
////					stop();	
////					SysTick_Wait10ms(200);     //wait	
////					//END turn LEFT		
////					
////					turnLeft++; turnRight=0;
////          count = 0;	out = 0;
////          F_R_L_Sensor();					
////					while((count<90)&&(out==0)){						
////						if (distance0<50) {
////							out =1; count = 70;
////						}
////						if ((distance2>100)&&(distance1<80)){
////							if(distance1<50){
////								GPIO_PORTF_DATA_R = 0x0A;											 
////								leftMove();
////								SysTick_Wait10ms(3);   //2
////								forwardMove();
////								SysTick_Wait10ms(4);	 //3
////								rightMove();
////								SysTick_Wait10ms(2);   //1  
////								stepBack();
////								SysTick_Wait10ms(1);	 //1											
////								stop();											 														
////							}
////							else if (distance1>50){	 
////								GPIO_PORTF_DATA_R = 0x0C;
////								rightMove();
////								SysTick_Wait10ms(2);    //2
////								forwardMove();
////								SysTick_Wait10ms(4);	  //3
////								leftMove();
////								SysTick_Wait10ms(2);    //2
////								stepBack();
////								SysTick_Wait10ms(1);		//1		
////								stop();											 								
////							}
////						}	
////            else if ((distance1<100)&&(distance2<100)) {
////							GPIO_PORTF_DATA_R = 0x06;								
////							moveStraight();
////							SysTick_Wait10ms(1);
////							stop();
////            }							
////            else if ((distance1>100)&&(distance2<80)) {
////              if (distance2>50) {
////								GPIO_PORTF_DATA_R = 0x0A;											 
////								leftMove();
////								SysTick_Wait10ms(3);   //2
////								forwardMove();
////								SysTick_Wait10ms(4);	 //3
////								rightMove();
////								SysTick_Wait10ms(2);   //1  
////								stepBack();
////								SysTick_Wait10ms(1);	 //1											
////								stop();											 								
////              }		
////							else if (distance2<50){	
////								GPIO_PORTF_DATA_R = 0x0C;
////								rightMove();
////								SysTick_Wait10ms(2);    //2
////								forwardMove();
////								SysTick_Wait10ms(4);	  //3
////								leftMove();
////								SysTick_Wait10ms(2);    //2
////								stepBack();
////								SysTick_Wait10ms(1);		//1		
////								stop();											 																
////						  }							
////            }
////						else if ((distance0>50)&&(distance1>100)
////							       &&(distance2>100)) {
////							GPIO_PORTF_DATA_R = 0x0C;
////							rightMove();
////							SysTick_Wait10ms(2);    //2
////							forwardMove();
////							SysTick_Wait10ms(4);	  //3
////							leftMove();
////							SysTick_Wait10ms(2);    //2
////							stepBack();
////							SysTick_Wait10ms(1);		//1		
////							stop();	
////              GPIO_PORTF_DATA_R = 0x0A;											 
////							leftMove();
////							SysTick_Wait10ms(3);   //2
////							forwardMove();
////							SysTick_Wait10ms(4);	 //3
////							rightMove();
////							SysTick_Wait10ms(2);   //1  
////							stepBack();
////							SysTick_Wait10ms(1);	 //1											
////							stop();																							
////						}
////						F_R_L_Sensor();
////						count++;
////					}
////					stop();
////					count = 0; out = 0; stop();
////					SysTick_Wait10ms(200);     //wait					
////					l = 0;  turn = 0;
////				}//END turn LEFT	
////				//stirr Left***********************************************
////				else if ((distance0>80)&&(distance1<80)
////									&&(distance2<80)&&(distance2>distance1)
////									&&(distance2-distance1>10)) {
////					GPIO_PORTF_DATA_R = 0x08;			//GREEN led
////					turnLeft=0; turnRight=0;	
////										 				 
////					if ((distance2>distance1)&&(distance2-distance1>10)){
////						pDistn0 = distance0; out = 0;
////						while(((distance0>80)&&(distance1<50)&&(out==0)) //40
////									||((distance0>80)&&(distance2>70)&&(out==0))) { //70
////							leftMove();
////							SysTick_Wait10ms(2);   //2
////							forwardMove();
////							SysTick_Wait10ms(3);	 //2
////							rightMove();
////							SysTick_Wait10ms(1);   //1  
////							stepBack();
////							SysTick_Wait10ms(1);	 //1											
////							stop();											 
////							F_R_L_Sensor();	
////							if(distance2>150) {
////								out = 1;
////							}
////							if ((distance2>70)||(distance1>70)) {
////								while((distance1>70)&&(distance1<150)
////									     &&(distance2<150)) {
////									rightMove();
////									F_R_L_Sensor();
////								}
////								stop();
////								F_R_L_Sensor();
////							}	
////						}
////						out = 0;
////					}
////					turn = 0;
////					F_R_L_Sensor();
////          rightMove();
////					SysTick_Wait10ms(1);  //3
////					stop();							
////				}
////        //END of stirr Left***************************************
////			 //stirr RIGTH***********************************************
////				else if ((distance0>80)&&(distance1<80)
////					         &&(distance2<80)&&(distance1>distance2)
////					         &&(distance1-distance2>10)) {
////					GPIO_PORTF_DATA_R = 0x0C;	//CYAN led
////          turnLeft=0; turnRight=0;		 

////					if ((distance1>distance2)&&(distance1-distance2>10)){
////						pDistn0 = distance0;
////						out = 0;
////						while(((distance0>80)&&(distance2<50)&&(out==0))  //40
////									||((distance0>80)&&(distance1>70)&&(out==0))) { //70
////							rightMove();
////							SysTick_Wait10ms(1);    //2
////							forwardMove();
////							SysTick_Wait10ms(3);	  //2
////							leftMove();
////							SysTick_Wait10ms(1);    //1
////							stepBack();
////							SysTick_Wait10ms(1);		//1		
////							stop();											 
////							F_R_L_Sensor();	
////							if (distance1>150) {
////								out = 1;
////              } 

////							if ((distance1>70)||(distance2>70)) {
////								while((distance2>70)&&(distance2<150)
////									    &&(distance1<150)) {
////									leftMove();
////									F_R_L_Sensor();
////								}
////								stop();
////								F_R_L_Sensor();
////							}
////						}
////						out = 0;
////					}
////					turn = 0;
////					F_R_L_Sensor();					
////          leftMove();
////					SysTick_Wait10ms(2);  //3
////					stop();
////					turn = 0;
////				}  	

////				//move FORWARD
////				else if (f==1) {
////					GPIO_PORTF_DATA_R = 0x08;	
////					SysTick_Wait10ms(50);
////					
////          count = 0;	out = 0;								
////					while((count<100)&&(out==0)){ 
////						moveStraight();
////						SysTick_Wait10ms(1);
////						stop();
////						count++;
////						F_R_L_Sensor();
////						if (distance0<50)
////							out =1;
////						if ((distance0>50)&&(distance1<60)) {
////							leftMove();
////							SysTick_Wait10ms(3);   //2
////							forwardMove();
////							SysTick_Wait10ms(4);	 //2
////							rightMove();
////							SysTick_Wait10ms(2);   //1  
////							stepBack();
////							SysTick_Wait10ms(1);	 //1											
////							stop();											 
////							F_R_L_Sensor();							
////						}
////						if ((distance0>50)&&(distance2<60)){
////							rightMove();
////							SysTick_Wait10ms(2);    //2
////							forwardMove();
////							SysTick_Wait10ms(4);	  //2
////							leftMove();
////							SysTick_Wait10ms(2);    //1
////							stepBack();
////							SysTick_Wait10ms(1);		//1		
////							stop();											 
////							F_R_L_Sensor();							
////						}
////					}
////					count = 0; out = 0; stop();					
////					f = 0; turn = 0;
////			  }	
////				//go STRAIGHT
////				else if ((distance0>100)&&(distance1>30)&&(distance1<60)
////					       &&(distance2>30)&&(distance2<60)){		
////					GPIO_PORTF_DATA_R = 0x04;	//led blue
////          turnLeft=0; turnRight=0;										 	
////					moveStraight();
////					turn = 0;
////			  }	
////        else if ((distance0>70)&&(distance0<100)){
////					stop();
////					GPIO_PORTF_DATA_R = 0x04;	//led blue
////					F_R_L_Sensor();
////					while(distance0>50) {
////						moveStraight();
////						F_R_L_Sensor();
////					}
////					stop();
////        }	
////        else {
////					GPIO_PORTF_DATA_R = 0x04;	//led blue
////					stop();
////				}	
//			  //END of go STRAIGHT					 
////			}////END of whiel(turn == 0)					
//			//not keep the intersection
////			if ((deadEnd == 1)&&(goal == 0)){ 
////				turn = 'U';
////			}	
////      //save the intersection to array			
////      else if ((deadEnd == 0)&&(goal == 0)){ 			
////				if (turn == 0x03){////***turn RF == 0x03	    
////					travalArray[index++] = 0x03;
////					travalArray[index++] = 'R';
////					travalArray[index++] = 'F';
////					turn = 'F';
////					f = 1;
////					turn = 0; 
////				}	     											
////				else if (turn == 0x05) {/////***turn LF ==0x05	 
////					travalArray[index++] = 0x05;
////					travalArray[index++] = 'L';
////					travalArray[index++] = 'F';
////					turn = 'F';
////					f = 1;
////					turn = 0; 
////				}	      				
////				else if (turn == 0x06) {/////***turn LR == 0x06 
////					travalArray[index++] = 0x06;
////					travalArray[index++] = 'L';
////					travalArray[index++] = 'R';
////					turn = 'R';					
////					r = 1;    
////					turn = 0; 
////				}									
////				else if (turn == 0x07) {/////***LRF == 0x07 
////					travalArray[index++] = 0x07;
////					travalArray[index++] = 'L';
////					travalArray[index++] = 'R';
////					travalArray[index++] = 'F';
////					turn = 'F';
////					f = 1;
////					turn = 0;
////				}			
////			}
////		}//END OF:"while(turn!='U')";
////		if (goal == 0){				
////			while (turn == 'U'){
////				deadEnd=0; 
////				DFS_1stRun = 'U';  			
////				for (i=0; i<4; i++)
////					arrayTurns[i] = 0;	     				
////				i = 0;				
////				//array that hold the turns:0x03,0x05,0x06,0x07
////        if ((travalArray[index]) == 0)
////					index--;				
////				/*////pop off the TOP stack and save values to array[4];
////				////0x07==LRF-->[0]=='F', [1]=='R', [2]=='L',[3]==0x07 
////				////0x06==LR--->[0]=='R', [1]=='L', [2]== 0, [3]==0x06 
////				////0x05==LF--->[0]=='F', [1]=='L', [2]== 0, [3]==0x05 
////				////0x03=RF---->[0]=='F', [1]=='R', [2]== 0, [3]==0x03*/
////				while (((DFS_1stRun>0x0F)&&(index>0))||
////					    ((DFS_1stRun>0x0F)&&(index==0))) {
////					DFS_1stRun = travalArray[index];	
////          travalArray[index--] = 0;
////					if (DFS_1stRun > 0x0F){
////						arrayTurns[i] = DFS_1stRun;	
////						i++;
////					}
////				}			
////				arrayTurns[3] = DFS_1stRun;					
////				////RF,LF=0x03,0x05
////				if ((arrayTurns[3] == 0x03)||(arrayTurns[3]==0x05)) {					
////					if ((arrayTurns[0]=='F')&&(arrayTurns[1]=='R')) {
////						deadEnd = 0;
////						turn = 'L';
////						index++;
////						travalArray[index++] = arrayTurns[3]; //push 0x03
////						travalArray[index++] = arrayTurns[1]; //push 'R'
////					}					
////					else if ((arrayTurns[0]=='F')&&(arrayTurns[1]=='L')){
////						deadEnd = 0;
////						turn = 'R';
////						index++;
////						travalArray[index++] = arrayTurns[3]; //push 0x05
////						travalArray[index++] = arrayTurns[1]; //push 'L'
////					}					
////				  /*////2ND TURN, deadEnd = 1;
////					////0x05==LF--->[0]=='L',[1]==0,[2]== 0,[3]==0x05 
////				  ////0x03=RF---->[0]=='R',[1]==0,[2]== 0,[3]==0x03 */
////					else if ((arrayTurns[0]=='R')||(arrayTurns[0]=='L')){
////					  deadEnd = 1;									 
////						if (arrayTurns[0]=='R')
////							turn = 'L';						
////						else if (arrayTurns[0]=='L')
////							turn = 'R';
////					}							
////				}//END OF: 0x03==RF, 0x05==LF
////				
////				////RL=0x06
////				else if (arrayTurns[3]==0x06) {						
////					if (arrayTurns[0]=='R') {
////						deadEnd = 0;
////						turn = 'F';
////						index++;
////						travalArray[index++] = arrayTurns[3]; //push 0x06
////						travalArray[index++] = arrayTurns[1]; //push 'L'
////					}					
////					else if (arrayTurns[0]=='L') {
////						deadEnd = 1;
////						turn = 'R';
////					}	
////				}//END OF: 0x06==LR
////				
////				////LRF=0x07
////				else if (arrayTurns[3]==0x07) {						
////					if (arrayTurns[0]=='F') {
////						deadEnd = 0;
////						turn = 'L';
////						index++;
////						travalArray[index++] = arrayTurns[3]; //push 0x07
////						travalArray[index++] = arrayTurns[2]; //push 'L'
////						travalArray[index++] = arrayTurns[1]; //push 'R'
////					}
////					else if (arrayTurns[0] == 'R') {
////						deadEnd = 0;
////						turn = 'F';
////						index++;
////						travalArray[index++] = arrayTurns[3]; //push 0x07
////						travalArray[index++] = arrayTurns[1]; //push 'L'
////					}
////					else if (arrayTurns[0]=='L') {
////						deadEnd = 1;	
////						turn = 'R';
////					}						
////				}//END OF: 0x07==LRF				
////				if (turn == 'R'){    
////					r = 1;
////					turn = 0;  //go back to while(turn==0)
////				}					
////				else if (turn == 'L'){
////					l = 1;
////					turn = 0; //go back to while(turn==0)
////				}				
////				else if (turn == 'F'){
////					f = 1;
////					turn = 0; //go back to while(turn==0)
////				}
////			}//END OF:"while(turn=='U')"	
////    }//END of if(goal==0)				
////		if (goal==1) {			
////			i = 0; ii = 0;
////			while (travalArray[i] != 0){
////				if ((i>0)&&(travalArray[i-1]>0x0F)&&
////					 (travalArray[i]>0x0F)) {
////					secndRunArray[ii-1] = travalArray[i];
////				}
////				else {
////					secndRunArray[ii] = travalArray[i];	
////					ii++;
////				}
////				i++; 
////			}
////			ii = 0;
////			while(secndRunArray[ii] != 0) {
////				UART_OutString("secndAry:");
////				if (secndRunArray[ii] == 70)
////					UART_OutString(" F");
////				else if (secndRunArray[ii] == 82)
////					UART_OutString(" R");
////				else if (secndRunArray[ii] == 76)
////					UART_OutString(" L");
////				else 
////					UART_OutUDec(secndRunArray[ii]);
////				OutCRLF();
////				ii++;
////			}
////			ii = (ii+1)/2;
////			OutCRLF();
////			UART_OutString("number of Turns secndArray: ");
////			UART_OutUDec(i);
////			UART_OutString("---");
////			UART_OutUDec(ii);
////			OutCRLF();
////			stop();
////			ii=0;
////			
////			//press sw2 2-time to get out loop
////			GPIO_PORTF_DATA_R = 0x00;
////			while(goal == 1){
////				GPIO_PORTF_DATA_R ^= 0x06; //led pink
////				SysTick_Wait10ms(50);
////				if (stp_intr==2)
////					goal = 2;
////			}
////			stp_intr = 0;
////		} //END OF if(goal==1)
////		stp_intr = 0;	
////		GPIO_PORTF_DATA_R = 0x00;
////		while(goal==3) {
////			stop();
////			GPIO_PORTF_DATA_R ^= 0x08; //led green
////			SysTick_Wait10ms(30);
////			if (stp_intr>0) {
////				goal = 0;
////				turn = 0;
////			}
////		}	
////	}//END OF while((goal == 0)||(goal==2)), 	
////}	
//////END OF Main
////void motorA(unsigned long speedA) {
////	GPIO_PORTB_DATA_R |= 0x01; //MotorA, foward	
////	PWM0A_Duty(speedA);  //40,000 == 100% , 100, 2500, 5000
////}
////void motorB(unsigned long speedB) {
////	GPIO_PORTB_DATA_R |= 0x02; //MotorB, foward	
////	PWM0B_Duty(speedB);	 //40,000 == 100% , 3000,10000, 10000		
////}

////void moveStraight(void) {
////  GPIO_PORTB_DATA_R |= 0x01; //MotorA, foward	
////	GPIO_PORTB_DATA_R |= 0x02; //MotorB, foward	
////	PWM0A_Duty(15000);   			 //40,000 == 100% , 8000
////	PWM0B_Duty(25000);		     //40,000 == 100% , 10000
////}
////void forwardMove(void) {
////	//move Forward	low PWM pulse
////	GPIO_PORTB_DATA_R |= 0x01; 	 //MotorA, foward
////	GPIO_PORTB_DATA_R |= 0x02;   //MotorB, foward
////	PWM0A_Duty(5000);   				 //40,000 == 100%	
////	PWM0B_Duty(5000);		      	 //40,000 == 100%		
////}
////void rightMove(void){
////		//stirr Right
////	GPIO_PORTB_DATA_R &= ~0x01;  //MotorA, backward	
////	GPIO_PORTB_DATA_R |= 0x02;   //MotorB, forward
////	PWM0A_Duty(35000);   				 //40,000 == 100%
////	PWM0B_Duty(5000);	
////}
////void leftMove(void) {
////	//stirr Left
////	GPIO_PORTB_DATA_R |= 0x01;   //MotorA, forward
////	GPIO_PORTB_DATA_R &= ~0x02;  //MotorB, backward
////	PWM0A_Duty(5000);   				 //40,000 == 100%
////	PWM0B_Duty(35000);	
////}
////void stepBack(void) {
////	//move Back	hight PWM pulse	
////	GPIO_PORTB_DATA_R &= ~0x01; //MotorA, backward	
////	GPIO_PORTB_DATA_R &= ~0x02; //MotorB, backward
////	PWM0A_Duty(35000);   				//40,000 == 100%	
////	PWM0B_Duty(35000);		      //40,000 == 100%	
////}
////void shiftRight(void) {	
////	//stirr Right
////	GPIO_PORTB_DATA_R &= ~0x01;  //MotorA, backward	
////	GPIO_PORTB_DATA_R |= 0x02;   //MotorB, forward
////	PWM0A_Duty(35000);   				 //40,000 == 100%
////	PWM0B_Duty(5000);		         //40,000 == 100%	
////	SysTick_Wait10ms(2);
////						
////	//move Forward	low PWM pulse
////	GPIO_PORTB_DATA_R |= 0x01; 	 //MotorA, foward
////	GPIO_PORTB_DATA_R |= 0x02;   //MotorB, foward
////	PWM0A_Duty(5000);   				 //40,000 == 100%	
////	PWM0B_Duty(5000);		      	 //40,000 == 100%	
////	SysTick_Wait10ms(5);	//2,5

////	//stirr Left
////	GPIO_PORTB_DATA_R |= 0x01;   //MotorA, forward
////	GPIO_PORTB_DATA_R &= ~0x02;  //MotorB, backward
////	PWM0A_Duty(5000);   				 //40,000 == 100%
////	PWM0B_Duty(35000);		       //40,000 == 100%	
////	SysTick_Wait10ms(1);
////	stop();
////}
////void shiftLeft(void) {
////	//stirr Left
////	GPIO_PORTB_DATA_R |= 0x01;   //MotorA, forward
////	GPIO_PORTB_DATA_R &= ~0x02;  //MotorB, backward
////	PWM0A_Duty(5000);   				 //40,000 == 100%
////	PWM0B_Duty(35000);		       //40,000 == 100%	
////	SysTick_Wait10ms(2);
////					
////	//move Forward	low PWM pulse
////	GPIO_PORTB_DATA_R |= 0x01; 	 //MotorA, foward
////	GPIO_PORTB_DATA_R |= 0x02;   //MotorB, foward
////	PWM0A_Duty(5000);   				 //40,000 == 100%	
////	PWM0B_Duty(5000);		      	 //40,000 == 100%	
////	SysTick_Wait10ms(5);	//2,5

////	//stirr Right
////	GPIO_PORTB_DATA_R &= ~0x01;  //MotorA, backward	
////	GPIO_PORTB_DATA_R |= 0x02;   //MotorB, forward
////	PWM0A_Duty(35000);   				 //40,000 == 100%
////	PWM0B_Duty(5000);		         //40,000 == 100%	
////	SysTick_Wait10ms(1);
////	stop();
////}
////void stop(void) {
////		GPIO_PORTB_DATA_R |= 0x01; 	//MotorA, foward	
////		GPIO_PORTB_DATA_R |= 0x02;  //MotorB, forward
////		PWM0A_Duty(35000);   				//10%	MotorA, foward
////		PWM0B_Duty(35000);		      //10%	MotorB, foward
////}
//////Timer0 Port PE4-5, distance0
////void timer0FrontDistance0(unsigned long *distance0) {
////  unsigned long distn0 = 0;
////	while ((distn0 == 0)||(distn0>5000)||(distn0<15)) {
////		GPIO_PORTE_DATA_R &= ~0x20;						 //PE5, Trigger is low for 2us
////		SysTick_Wait2us(1);
////		GPIO_PORTE_DATA_R |= 0x20;    				 //PE5, Trigger is high for 10us
////		SysTick_Wait10us(1);
////		GPIO_PORTE_DATA_R &= ~0x20;   				 //PE5 is low
////		while ((GPIO_PORTE_DATA_R&0x10)==0);	 //PE4 input is low, Echo
////		while (GPIO_PORTE_DATA_R&0x10) {    	 //PE4 input is high, Echo
////			TIMER0_CTL_R = 0x00000001;        	 //enable TIMER0A
////		}	
////		TIMER0_ICR_R = TIMER_ICR_TATOCINT;     //acknowledge TIMER0A timeout
////		TIMER0_CTL_R = 0x00000000;             //disable TIMER0A
////		
////		distn0 = ((count0/2) * 0.0343)*10;     //in milimeters	
////		count0 = 0;//
////	}
////	*distance0 = distn0;
////}
//////Timer1 Port PD2-3, distance1, Right
////void timer1RightDistance1_1(unsigned long *distance1) {
////	unsigned long distn1 = 0;
////	while ((distn1==0)||(distn1<15)||(distn1>5000)) {
////		GPIO_PORTD_DATA_R &= ~0x08;							//PD3 trigger is low for 2us
////		SysTick_Wait2us(1);
////		GPIO_PORTD_DATA_R |= 0x08;    					//PD3 trigger is high for 10us
////		SysTick_Wait10us(1);
////		GPIO_PORTD_DATA_R &= ~0x08;   					//PD3 is low
////		while ((GPIO_PORTD_DATA_R&0x04)==0);	  //PD2 echo input is low
////		while ((GPIO_PORTD_DATA_R&0x04)) {      //PD2 echo input is high
////			TIMER1_CTL_R = 0x00000001;        		//enable TIMER1A
////		}	
////		TIMER1_ICR_R = TIMER_ICR_TATOCINT;  		// acknowledge TIMER1A timeout
////		TIMER1_CTL_R = 0x00000000;          		// disable TIMER1A during setup
////		distn1 = ((count1/2) * 0.0343)*10; //in milimeters	//
////		count1 = 0;//
////	}
////	*distance1 = distn1;
////}
//////Timer2 Port PE2-3, distance2 Left
////void timer2LeftDistance2_2(unsigned long *distance2) {
////	unsigned long distn2 = 0;
////	while ((distn2==0)||(distn2<15)||(distn2>5000)) {
////	//Timer2 Port PE2-3, distance2,2
////	GPIO_PORTE_DATA_R &= ~0x08;						  //PE3 trigger is low for 2us
////	SysTick_Wait2us(1);
////	GPIO_PORTE_DATA_R |= 0x08;    			    //PE3 trigger is high for 10us
////	SysTick_Wait10us(1);
////	GPIO_PORTE_DATA_R &= ~0x08;   			    //PE3 is low
////	while ((GPIO_PORTE_DATA_R&0x04)==0);    //PE2 echo input is low
////	while (GPIO_PORTE_DATA_R&0x04){         //PE2 echo input is high
////		TIMER2_CTL_R = 0x00000001;     	      //enable TIMER0A
////	}				
////	TIMER2_ICR_R = TIMER_ICR_TATOCINT;      //acknowledge TIMER2A timeout
////	TIMER2_CTL_R = 0x00000000;
////		distn2 = ((count2/2) * 0.0343)*10; //in milimeters	
////		count2 = 0;
////	}
////	*distance2 = distn2;	
////}

////void PortF_Init(void){ 
////	volatile unsigned long delay;
////  SYSCTL_RCGC2_R |= 0x20;         // (1) activate Port F
////  delay = SYSCTL_RCGC2_R;         // allow time for clock to stabilize
////  GPIO_PORTF_LOCK_R = 0x4C4F434B; // (2) unlock Port F lock
////  GPIO_PORTF_CR_R = 0x1F;         //    enable commit (allow configuration changes) on PF4-0
////  GPIO_PORTF_AMSEL_R = 0x00;      // (3) disable analog functionality on PF4-0
////  GPIO_PORTF_PCTL_R = 0x00000000; // (4) configure PF4-0 as GPIO
////	GPIO_PORTF_DIR_R &= ~0x10;      // (c) make PF4 in (built-in button)
////	GPIO_PORTF_DIR_R &= ~0x01;      // (c) make PF0 in (built-in button)
////  GPIO_PORTF_DIR_R |= 0x0E;       // (5) PF4 and PF0 in, PF3-1 out
////	GPIO_PORTF_DEN_R |= 0x01;       //    enable digital I/O on PF0 
////	GPIO_PORTF_DEN_R |= 0x10;       //    enable digital I/O on PF4 
////  GPIO_PORTF_DEN_R = 0x1F;        // (7) enable digital I/O on PF4-0
////  GPIO_PORTF_AFSEL_R = 0x00;      // (6) disable alt funct on PF4-0
////  GPIO_PORTF_PUR_R |= 0x11;     	//     enable weak pull-up on PF4,0
////  GPIO_PORTF_IS_R &= ~0x11;     	// (d) PF4,PF0 is edge-sensitive
////  GPIO_PORTF_IBE_R &= ~0x11;    	//     PF4,PF0 is not both edges
////  GPIO_PORTF_IEV_R &= ~0x11;    	//     PF4,PF0 falling edge event
////  GPIO_PORTF_ICR_R = 0x11;      	// (e) clear flags 4,0
////  GPIO_PORTF_IM_R |= 0x11;      	// (f) arm interrupt on PF4,PF0
////  NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00400000; // (g) priority 2
////  NVIC_EN0_R = 0x40000000;      	// (h) enable interrupt 30 in NVIC
////}

//////PB6, PB7 is PWM, PB0, PB1 is Direction (PB6-->PB0, PB7-->PB1)
////void PortB_Init(void){
////	unsigned long volatile delay;
////	SYSCTL_RCGC2_R |= 0x02;           // 1) activate Port B
////  delay = SYSCTL_RCGC2_R;           // allow time for clock to stabilize
////  GPIO_PORTB_AMSEL_R &= ~0x03;      // 3) disable analog functionality on PB0, PB1
////  GPIO_PORTB_PCTL_R &= ~0x000000FF; // 4) configure PB0, PB1 as GPIO
////  GPIO_PORTB_DIR_R |= 0x03;         // 5) PB0, PB1 as output
////  GPIO_PORTB_AFSEL_R &= ~0x03;      // 6) disable alt funct on PB0, PB1
////  GPIO_PORTB_DEN_R |= 0x03;         // 7) enable digital I/O on PB0, PB1
////	
////	GPIO_PORTB_AMSEL_R = 0x00;        // 3) disable analog functionality on PB
////  GPIO_PORTB_PCTL_R &= ~0x00000F00; // 4) configure PB2 as GPIO
////  GPIO_PORTB_DIR_R |= 0x04;         // 5) PB2 as output
////  GPIO_PORTB_AFSEL_R &= ~0x04;      // 6) disable alt funct on PB
////  GPIO_PORTB_DEN_R |= 0x04;         // 7) enable digital I/O on PB
////}

////void PortC_Init(void){  
////	unsigned long volatile delay;
////  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOC; // activate port C
////  delay = SYSCTL_RCGC2_R;
////  GPIO_PORTC_DIR_R &= ~0x40;    	  		// make PC6 as input
////	GPIO_PORTC_DIR_R |= 0x80;         		// make PC7 as output
////  GPIO_PORTC_AFSEL_R &= ~0xC0;      		// disable alt funct on PC6-7
////  GPIO_PORTC_DEN_R |= 0xC0;         		// enable digital I/O on PC6-7
////  GPIO_PORTC_PCTL_R &= ~0xFF000000; 		// configure PC6-7 as GPIO
////  GPIO_PORTC_AMSEL_R &= ~0xC0;      		// disable analog functionality on PC6-7
////}

////void PortD_Init(void){  
////	unsigned long volatile delay;
////  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOD; // activate port D
////  delay = SYSCTL_RCGC2_R;
////  GPIO_PORTD_DIR_R &= ~0x04;    	  		// make PD2 as input
////	GPIO_PORTD_DIR_R |= 0x08;         		// make PD3 as output
////  GPIO_PORTD_AFSEL_R &= ~0x0C;      		// disable alt funct on PD2-3
////  GPIO_PORTD_DEN_R |= 0x0C;         		// enable digital I/O on PD2-3
////  GPIO_PORTD_PCTL_R &= ~0x0000FF00; 		// configure PD2-3 as GPIO
////  GPIO_PORTD_AMSEL_R &= ~0x0C;      		// disable analog functionality on PD2-3
////}

////void PortE_Init(void){  
////	unsigned long volatile delay;
////  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOE; // activate port E
////  delay = SYSCTL_RCGC2_R;
////  GPIO_PORTE_DIR_R &= ~0x04;    	  		// make PE2 as input
////	GPIO_PORTE_DIR_R |= 0x08;         		// make PE3 as output
////  GPIO_PORTE_AFSEL_R &= ~0x0C;      		// disable alt funct on PE2-3
////  GPIO_PORTE_DEN_R |= 0x0C;         		// enable digital I/O on PE2-3
////  GPIO_PORTE_PCTL_R &= ~0x0000FF00; 		// configure PE2-3 as GPIO
////  GPIO_PORTE_AMSEL_R &= ~0x0C;      		// disable analog functionality on PE2-3
////	
////  GPIO_PORTE_DIR_R &= ~0x10;    	  		// make PE4 as input
////	GPIO_PORTE_DIR_R |= 0x20;         		// make PE5 as output
////  GPIO_PORTE_AFSEL_R &= ~0x30;      		// disable alt funct on PE4-5
////  GPIO_PORTE_DEN_R |= 0x30;         		// enable digital I/O on PE4-5
////  GPIO_PORTE_PCTL_R &= ~0x00FF0000; 		// configure PE4-5 as GPIO
////  GPIO_PORTE_AMSEL_R &= ~0x30;      		// disable analog functionality on PE4-5
////}

////void PortA_Init(void){  
////	unsigned long volatile delay;
////  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA; // activate port A
////  delay = SYSCTL_RCGC2_R;
////  GPIO_PORTA_DIR_R &= ~0x04;    	  		// make PA2 as input
////	GPIO_PORTA_DIR_R |= 0x08;         		// make PA3 as output
////  GPIO_PORTA_AFSEL_R &= ~0x0C;      		// disable alt funct on PA2-3
////  GPIO_PORTA_DEN_R |= 0x0C;         		// enable digital I/O on PA2-3
////  GPIO_PORTA_PCTL_R &= ~0x0000FF00; 		// configure PA2-3 as GPIO
////  GPIO_PORTA_AMSEL_R &= ~0x0C;      		// disable analog functionality on PA2-3
////}

///*
//// Color    LED(s) PortF
//// dark     ---    0
//// red      R--    0x02
//// blue     --B    0x04
//// green    -G-    0x08
//// yellow   RG-    0x0A
//// sky blue -GB    0x0C
//// white    RGB    0x0E
//// pink     R-B    0x06
//*/
//////****************************************************************************
//////NOTE: Kp==0.008, make PID function

//#include <stdio.h>  // If a library is standard C library use the <> braces
//#include <stdlib.h>
//#include <stdint.h>
//#include <string.h>
//#include <limits.h>
//#include "UART.h"
//#include "PLL.h"
//#include "PWM.h"
//#include "SysTick.h"
//#include "Timer0.h"
//#include "Timer1.h"
//#include "Timer2.h"
//#include "tm4c123gh6pm.h"

////// Sys. Handlers 12 to 15 Priority
////#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
////#define NVIC_SYS_PRI3_R         (*((volatile unsigned long *)0xE000ED20))  
////#define NVIC_ST_CTRL_R          (*((volatile unsigned long *)0xE000E010))
////#define NVIC_ST_RELOAD_R        (*((volatile unsigned long *)0xE000E014))
////#define NVIC_ST_CURRENT_R       (*((volatile unsigned long *)0xE000E018))

//unsigned long distance0=0, distance1=0, distance2=0;
//unsigned long count0=0, count1=0, count2=0;
//unsigned char stp_intr=0, blink_intr=0;
//unsigned long one_second_count = 0;

//long StartCritical (void);    // previous I bit, disable interrupts
//void EndCritical(long sr);    // restore I bit to previous value
//void WaitForInterrupt(void);
//void DisableInterrupts(void); 
//void EnableInterrupts(void);
//void PortF_Init(void);
//void PortE_Init(void);
//void PortA_Init(void);
//void PortB_Init(void);
//void PortC_Init(void);
//void PortD_Init(void);

//void timer0FrontDistance0(unsigned long *distance0);
//void timer1RightDistance1_1(unsigned long *distance1);
//void timer2LeftDistance2_2(unsigned long *distance2); 
//void stop(void);
//void shiftLeft(void);
//void shiftRight(void);
//void moveStraight(void);
//void stepBack(void);
//void forwardMove(void);
//void rightMove(void);
//void leftMove(void);
//void speedingA_stirrLeft (unsigned char error);
//void speedingB_stirrRight(unsigned char error);
//void myPIDcontrol (double Kpp, double Kii, double Kdd);
//void motorA(unsigned long speedA);
//void motorB(unsigned long speedB);

//void GPIOPortF_Handler(void){ 
//	if (GPIO_PORTF_RIS_R&0x01){
//		GPIO_PORTF_ICR_R = 0x01; //acknldge intr sw2
//		if (stp_intr==3)
//			stp_intr = 1;
//		else
//		  stp_intr++;
//	}
//	else if (GPIO_PORTF_RIS_R&0x10){
//		GPIO_PORTF_ICR_R = 0x10; //acknldge intr sw1
//		if (blink_intr>0)
//			blink_intr = 0;
//		blink_intr++;
//	}
//}

//void UserTask(void){		//Timer0  
//	if (GPIO_PORTE_DATA_R&0x10) //PE4 as input
//		count0 = count0 + 1;
//}

//void UserTask1(void){		//Timer1
//	if (GPIO_PORTD_DATA_R&0x04) //PD2 as input
//		count1 = count1 + 1;
//}

//void UserTask2(void){		//Timer2
//	if (GPIO_PORTE_DATA_R&0x04)  //PE2 as input
//		count2 = count2 + 1;
//}
//void OutCRLF(void){
//  UART_OutChar(CR);
//  UART_OutChar(LF);
//}
//void F_R_L_Sensor(void) {
//		//Timer0 Port PE4-5, distance0	
//		timer0FrontDistance0(&distance0);				
//		//Timer1 Port PD2-3, distance1, 1
//		timer1RightDistance1_1(&distance1);	
//		//Timer2 Port PE2-3, distance2, 2
//		timer2LeftDistance2_2(&distance2); 
//}

//int main (void) {
//	unsigned long index = 0, i = 0, ii = 0;
//	unsigned long count = 0;
//	unsigned char goTurn = 0, out=0, error=0;
//	unsigned char turnLeft = 0, turnRight = 0;
//	unsigned char r=0, l=0, f=0, setPoint=0;
//	unsigned char DFS_1stRun;
//	unsigned char turn = 0, deadEnd=0, goal=0;
//	unsigned char arrayTurns[4] = {0, 0, 0, 0};	
//	unsigned char travalArray[250]; 
//	unsigned char secndRunArray[250];
//	unsigned long speedA=3000, speedB=5000;
//	signed long Ep=0, Ed=0, Ei=0, lastError=0;
//	double Kp=0.008, Ki=0, Kd=0;    
//	unsigned long loopCount=0;
//		
//	DisableInterrupts(); 
//  PLL_Init();  // bus clock at 80 MHz==80,000,000Hz
//	PortF_Init();
//	PortE_Init();
//	PortA_Init();
//	PortB_Init();
//	PortC_Init();
//	PortD_Init();
//	SysTick_Init(); 
//	UART_Init();  																
//																
//	Timer0_Init(&UserTask,80);   // 1us interrupt
//	Timer1_Init(&UserTask1,80);  // 1us interrupt
//	Timer2_Init(&UserTask2,80);  // 1us interrupt
//	EnableInterrupts();															
//																
//	PWM0A_Init(40000,15000);     // initi8alize PWM0, 1000 Hz
//	PWM0B_Init(40000,15000);     // initialize PWM0, 1000 Hz, 50% duty
//	
//  GPIO_PORTF_DATA_R = 0x04;		 // Blue led																
//	GPIO_PORTB_DATA_R |= 0x01; 	 // MotorA foward	
//	GPIO_PORTB_DATA_R |= 0x02;   // MotorB foward
//	PWM0A_Duty(speedA);   			 //40,000 == 100%
//	PWM0B_Duty(speedB);		       //40,000 == 100% 	
//  GPIO_PORTF_DATA_R = 0x04;		 // Blue led

//	for (unsigned char t=0; t<250; t++)
//		travalArray[t] = 0;
//	for (unsigned char s=0; s<250; s++)
//	  secndRunArray[s] = 0;
//		
//	while(distance0<150) {
//		stop();
//		F_R_L_Sensor();
//	}
//	OutCRLF();  OutCRLF();
//	UART_OutString("filter distance0---");
//	OutCRLF();
//	
//////initially, turn = 0, turn!='U';	
//	while ((goal == 0)||(goal == 2)) {
//		if(goal==2) {
//			GPIO_PORTF_DATA_R = 0x00;
//			count = 0;
//			while(count<10) {
//				GPIO_PORTF_DATA_R ^= 0x04;	//led blue blinking
//				SysTick_Wait10ms(10);
//				count++;
//			}
//			count = 0;
//			turn = 0;
//			GPIO_PORTB_DATA_R |= 0x01; 	 // MotorA foward	
//			GPIO_PORTB_DATA_R |= 0x02;   // MotorB foward
//		}
//		while (turn != 'U') {	
//			while (turn == 0){ 
//				F_R_L_Sensor();	

//				//***turn RF == 0x03 cyane
//				if ((distance0>120)&&(distance0<400)
//						&&(distance1>150)&&(distance1<400)
//						&&(distance2>30)&&(distance2<70)
//						&&(distance1>distance2)
//						&&(r==0)&&(f==0)) {
//					stop(); 
//					GPIO_PORTF_DATA_R = 0x0C;						
//						
//				  count=0; out = 0; 
//				 	while((count<5)) {
//						GPIO_PORTF_DATA_R ^= 0x0C;//cyane blinking
//						SysTick_Wait10ms(5);
//					  count++;
//					}
//					count=0;
//					
//					F_R_L_Sensor();
//					if (distance1<150)
//						out = 1;					
//				  if((turn == 0)&&(goal==0)&&(out==0)){
//						turn = 0x03;
//				  }
//				  else if((turn==0)&&(goal==2)&&(out==0)){
//						ii++;
//					  if (secndRunArray[ii]==82)
//							r = 1;
//					  else if (secndRunArray[ii]==70)
//					    f = 1;
//					  OutCRLF();
//				  }		
//          if (out == 1) {
//						count=0;
//						while(count<5) {
//							GPIO_PORTF_DATA_R ^= 0x04;
//							SysTick_Wait10ms(1);
//							count++;
//						}
//						count=0;						
//          }	
//          out = 0; turnLeft=0; turnRight=0;				
//				}
//				//***turn LF ==0x05	green		
//				else if ((distance0>120)&&(distance0<400)
//								 &&(distance1>30)&&(distance1<70)
//								 &&(distance2>150)&&(distance2<400)
//								 &&(distance1<distance2)
//								 &&(l==0)&&(f==0)) {			 
//					stop(); 
//				  GPIO_PORTF_DATA_R = 0x08;//green blinking
//									 
//				  count=0; out = 0;
//				  while((count<5)) {
//						GPIO_PORTF_DATA_R ^= 0x08;
//						SysTick_Wait10ms(5);
//						count++;
//				  }
//				  count=0; 
//					
//					F_R_L_Sensor();						
//					if (distance2<150)
//						out = 1;			 
//				  if((turn == 0)&&(goal==0)&&(out==0)){
//					  turn = 0x05;	
//				  }
//				  else if((turn==0)&&(goal==2)&&(out==0)){
//					  ii++;
//					  if (secndRunArray[ii]==70){
//						  f = 1;
//					  }
//						else if (secndRunArray[ii]==76) {
//							l = 1;
//						}
//					}  
//          if (out == 1) {
//						count=0;
//						while(count<5) {
//							GPIO_PORTF_DATA_R ^= 0x04;
//							SysTick_Wait10ms(1);
//							count++;
//						}
//						count=0;						
//          }	
//          out = 0;	turnLeft=0; turnRight=0;				
//				}
//				//***turn LR == 0x06 yellow
//				else if ((distance0>20)&&(distance0<80)
//								 &&(distance1>100)&&(distance1<300) 
//								 &&(distance2>100)&&(distance2<300)
//								 &&(r==0)&&(l==0)) {											
//					stop();				 
//					GPIO_PORTF_DATA_R = 0x0A;//yellow blinking
//									 
//				  count=0;
//				  while(count<5) {
//						GPIO_PORTF_DATA_R ^= 0x0A;//yellow blinking
//						SysTick_Wait10ms(5);
//						count++;
//				  }
//				  count=0; out = 0;
//					
//          stop();
//					F_R_L_Sensor();						
//					if ((distance1<100)||(distance2<100)
//						  ||(distance0>80))
//						out = 1;														 
//					if((turn == 0)&&(goal==0)&&(out==0)){
//						turn = 0x06;
//            if ((turnLeft==3)||(turnRight==3)){
//							goal = 1;
//						  turn = 'U';
//            }							
//					}
//					else if((turn==0)&&(goal==2)&&(out==0)){
//						ii++;
//						if (secndRunArray[ii]==82){
//							r = 1;
//						}
//						else if(secndRunArray[ii]==76) {
//							l = 1;
//						}
//						OutCRLF();
//						if ((turnLeft==3)||(turnRight==3)) {
//							goal = 3;
//							turn = 'U';
//						}
//					}		
//          if (out == 1) {
//						count=0;
//						while(count<5) {
//							GPIO_PORTF_DATA_R ^= 0x04;
//							SysTick_Wait10ms(1);
//							count++;
//						}
//						count=0;						
//          }	
//          out = 0; turnLeft=0; turnRight=0;				
//				}
//				//STOP
//				else if ((distance0>20)&&(distance0<40)
//								 &&(distance1>20)&&(distance2>20)
//								 &&(distance1<60)&&(distance2<60)){			 
//					stop();	stp_intr = 0;	goTurn = 0;
//					GPIO_PORTF_DATA_R = 0x02;					 
//					
//					count = 0; out = 0;
//					while ((count<5)&&(out==0)) {
//						F_R_L_Sensor();
//						GPIO_PORTF_DATA_R ^= 0x02; //led red
//						SysTick_Wait10ms(10);
//						count++;	
//						if (distance0 <50) {
//							out = 1;
//						}
//					}
//					count = 0;	out = 0;
//					if ((distance0>50)){
//						turn = 0;
//						goTurn = 0;
//					}
//					else if((distance0<50)&&(distance1<80)
//						      &&(distance2<80)&&(stp_intr==0)) {
//						goTurn = 1;
//						deadEnd = 1;
//						turn = 0;					    		  
//					}					
//					if(goTurn==1) {
//						GPIO_PORTF_DATA_R = 0x02;	
//						SysTick_Wait10ms(50);       //wait
//            stepBack();
//						SysTick_Wait10ms(15);
//						stop();
//						SysTick_Wait10ms(50);				//wait
//						
//						//U-Turn						
//						GPIO_PORTB_DATA_R |= 0x01; 	  //MotorA, backward	
//						GPIO_PORTB_DATA_R &= ~0x02;  	//MotorB, foward
//						PWM0A_Duty(100);   					  //40,000 == 100%		
//						PWM0B_Duty(39000);		        //40,000 == 100%	
//						SysTick_Wait10ms(22);    		  //turn 					
//						stop();
//						//END of U-turn	
//						
//						F_R_L_Sensor();
//						if (distance0>70) {
//							SysTick_Wait10ms(50);				//wait
//							forwardMove();					
//							SysTick_Wait10ms(10);  
//							stop();
//							SysTick_Wait10ms(50);				//wait

//							GPIO_PORTB_DATA_R |= 0x01; 	  //MotorA, backward	
//							GPIO_PORTB_DATA_R &= ~0x02;  	//MotorB, foward
//							PWM0A_Duty(100);   					  //40,000 == 100%		
//							PWM0B_Duty(39000);		        //40,000 == 100%	
//							SysTick_Wait10ms(20);    		  //turn 										
//							stop(); goTurn = 0;	
//						}
//						else {
//							GPIO_PORTB_DATA_R |= 0x01; 	  //MotorA, backward	
//							GPIO_PORTB_DATA_R &= ~0x02;  	//MotorB, foward
//							PWM0A_Duty(100);   					  //40,000 == 100%		
//							PWM0B_Duty(39000);		        //40,000 == 100%	
//							SysTick_Wait10ms(20);    		  //turn 										
//							stop(); goTurn = 0;	
//						}
//						
//            SysTick_Wait10ms(100);           //wait
//						loopCount=0;
//					}
//					turnLeft=0; turnRight=0;
//					GPIO_PORTF_DATA_R = 0x00;
//				}	
//				//turn RIGTH
///*				else if(((distance0>30)&&(distance0<80)
//								&&(distance1>100)&&(distance1<500)
//								&&(distance2>20)&&(distance2<80)
//								&&(distance1>distance2))
//								||(r == 1)){//RIGHT TURN																	         
//					stop();	
//					GPIO_PORTF_DATA_R = 0x0E;	
//									
//          count = 0;									
//					while((count<10)&&(r==0)){
//						F_R_L_Sensor();
//						SysTick_Wait10ms(1); 
//						if (r==1)
//							GPIO_PORTF_DATA_R ^= 0x0E;	
//						else if (r==0)
//							GPIO_PORTF_DATA_R = 0x0E;	
//						count++;
//					}
//					count = 0;
//					
//					goTurn = 0;
//					if (((distance0<80)&&(distance1>100))||(r==1)) {
//						goTurn = 1;
//					}
//					if (goTurn==1) {
//						F_R_L_Sensor();
//						if (distance0<50) {
//							stepBack();
//							SysTick_Wait10ms(10);
//							stop();	
//            }
//            F_R_L_Sensor();
//            if (distance0>80) {
//							forwardMove();
//							SysTick_Wait10ms(5);
//							stop();	
//            }							
//						SysTick_Wait10ms(100);  //wait
//						//one time turn RIGHT
//						GPIO_PORTB_DATA_R &= ~0x01; //MotorA, backward	
//						GPIO_PORTB_DATA_R |= 0x02;  //MotorB, foward
//						PWM0A_Duty(39000);   			  //40,000 == 100%		
//						PWM0B_Duty(500);		        //40,000 == 100%
//						SysTick_Wait10ms(20);    							
//						stop();	
//						SysTick_Wait10ms(100);      //wait
//            turnLeft=0; turnRight++;						
//						//END turn Right		
//					}
//					goTurn = 0;
//					
//          count = 0;	out = 0;
//          F_R_L_Sensor();					
//					while((count<150)&&(out==0)){						
//						if ((distance1>100)&&(distance2<100)){
//							if((distance0>50)&&(distance2<50)){
//								GPIO_PORTF_DATA_R = 0x0C;
//								rightMove();
//								SysTick_Wait10ms(2);    //2
//								forwardMove();
//								SysTick_Wait10ms(4);	  //3
//								leftMove();
//								SysTick_Wait10ms(2);    //2
//								stepBack();
//								SysTick_Wait10ms(1);		//1		
//								stop();											 
//								F_R_L_Sensor();								
//							}
//							else if ((distance0>50)&&(distance2>50)){	 
//								GPIO_PORTF_DATA_R = 0x0A;											 
//								leftMove();
//								SysTick_Wait10ms(3);   //2
//								forwardMove();
//								SysTick_Wait10ms(4);	 //3
//								rightMove();
//								SysTick_Wait10ms(2);   //1  
//								stepBack();
//								SysTick_Wait10ms(1);	 //1											
//								stop();											 
//								F_R_L_Sensor();	
//							}
//						}	
//            else if ((distance0>50)&&(distance1<100)
//							       &&(distance2<100)) {
//							GPIO_PORTF_DATA_R = 0x0E;								
//							moveStraight();
//            }							
//            else if ((distance2>100)&&(distance1<80)) {
//              if ((distance0>50)&&(distance1>50)) {
//								GPIO_PORTF_DATA_R = 0x0C;
//								rightMove();
//								SysTick_Wait10ms(2);    //2
//								forwardMove();
//								SysTick_Wait10ms(4);	  //3
//								leftMove();
//								SysTick_Wait10ms(2);    //2
//								stepBack();
//								SysTick_Wait10ms(1);		//1		
//								stop();											 
//								F_R_L_Sensor();
//              }		
//							else if ((distance0>50)&&(distance1<50)){	
//								GPIO_PORTF_DATA_R = 0x0A;											 
//								leftMove();
//								SysTick_Wait10ms(3);   //2
//								forwardMove();
//								SysTick_Wait10ms(4);	 //3
//								rightMove();
//								SysTick_Wait10ms(2);   //1  
//								stepBack();
//								SysTick_Wait10ms(1);	 //1											
//								stop();											 
//								F_R_L_Sensor();	
//						  }							
//            }
//						else if ((distance0>50)&&(distance1>100)
//							       &&(distance2>100)) {
//							rightMove();
//							SysTick_Wait10ms(2);    //2
//							forwardMove();
//							SysTick_Wait10ms(4);	  //3
//							leftMove();
//							SysTick_Wait10ms(2);    //2
//							stepBack();
//							SysTick_Wait10ms(1);		//1		
//							stop();		
//							leftMove();
//							SysTick_Wait10ms(3);   //2
//							forwardMove();
//							SysTick_Wait10ms(4);	 //3
//							rightMove();
//							SysTick_Wait10ms(2);   //1  
//							stepBack();
//							SysTick_Wait10ms(1);	 //1											
//							stop();																
//						}
//						F_R_L_Sensor(); stop();
//						count++;
//					}
//					stop(); loopCount=50;
//					count = 0; out = 0; stop();
//					SysTick_Wait10ms(100);     //wait	
//					turn = 0; r = 0;
//				}//END turnRIGTH	

//				//turn LEFT
//				else if (((distance0>30)&&(distance0<80)
//								 &&(distance1>20)&&(distance1<80)
//								 &&(distance2>100)&&(distance2<500)
//								 &&(distance2>distance1))
//								 ||(l == 1)){//LEFT TURN										 
//          stop();		 
//					GPIO_PORTF_DATA_R = 0x06;							
//					 
//					count = 0;
//					while(count<10){
//						SysTick_Wait10ms(1); 
//						if (l==1)
//							GPIO_PORTF_DATA_R ^= 0x06;	
//						else if (l==0)
//							GPIO_PORTF_DATA_R = 0x06;	
//						count++;
//					}
//					count = 0;
//					
//					F_R_L_Sensor();
//					if (distance0<50) {
//						stepBack();
//						SysTick_Wait10ms(10);
//						stop();	
//					}
//					F_R_L_Sensor();
//					if (distance0>80) {
//						forwardMove();
//						SysTick_Wait10ms(5);
//						stop();	
//					}
//					
//					SysTick_Wait10ms(100);     //wait	
//					//one time turn LEFT
//					GPIO_PORTB_DATA_R |= 0x01; //MotorA, forward
//					GPIO_PORTB_DATA_R &= ~0x02;//MotorB, backward
//					PWM0A_Duty(500);   			   //40,000 == 100%		
//					PWM0B_Duty(39000);		     //40,000 == 100%
//					SysTick_Wait10ms(20);    							
//					stop();	
//					SysTick_Wait10ms(100);     //wait	
//					//END turn LEFT		
//					
//					turnLeft++; turnRight=0;
//          count = 0;	out = 0;
//          F_R_L_Sensor();					
//					while((count<150)&&(out==0)){						
//						if (distance0<50) {
//							out =1; count = 150;
//						}
//						if ((distance2>100)&&(distance1<80)){
//							if(distance1<50){
//								GPIO_PORTF_DATA_R = 0x0A;											 
//								leftMove();
//								SysTick_Wait10ms(3);   //2
//								forwardMove();
//								SysTick_Wait10ms(4);	 //3
//								rightMove();
//								SysTick_Wait10ms(2);   //1  
//								stepBack();
//								SysTick_Wait10ms(1);	 //1											
//								stop();											 														
//							}
//							else if (distance1>50){	 
//								GPIO_PORTF_DATA_R = 0x0C;
//								rightMove();
//								SysTick_Wait10ms(2);    //2
//								forwardMove();
//								SysTick_Wait10ms(4);	  //3
//								leftMove();
//								SysTick_Wait10ms(2);    //2
//								stepBack();
//								SysTick_Wait10ms(1);		//1		
//								stop();											 								
//							}
//						}	
//            else if ((distance1<100)&&(distance2<100)) {
//							GPIO_PORTF_DATA_R = 0x06;								
//							moveStraight();
//            }							
//            else if ((distance1>100)&&(distance2<80)) {
//              if (distance2>50) {
//								GPIO_PORTF_DATA_R = 0x0A;											 
//								leftMove();
//								SysTick_Wait10ms(3);   //2
//								forwardMove();
//								SysTick_Wait10ms(4);	 //3
//								rightMove();
//								SysTick_Wait10ms(2);   //1  
//								stepBack();
//								SysTick_Wait10ms(1);	 //1											
//								stop();											 								
//              }		
//							else if (distance2<50){	
//								GPIO_PORTF_DATA_R = 0x0C;
//								rightMove();
//								SysTick_Wait10ms(2);    //2
//								forwardMove();
//								SysTick_Wait10ms(4);	  //3
//								leftMove();
//								SysTick_Wait10ms(2);    //2
//								stepBack();
//								SysTick_Wait10ms(1);		//1		
//								stop();											 																
//						  }							
//            }
//						else if ((distance0>50)&&(distance1>100)
//							       &&(distance2>100)) {
//							GPIO_PORTF_DATA_R = 0x0C;
//							rightMove();
//							SysTick_Wait10ms(2);    //2
//							forwardMove();
//							SysTick_Wait10ms(4);	  //3
//							leftMove();
//							SysTick_Wait10ms(2);    //2
//							stepBack();
//							SysTick_Wait10ms(1);		//1		
//							stop();	
//              GPIO_PORTF_DATA_R = 0x0A;											 
//							leftMove();
//							SysTick_Wait10ms(3);   //2
//							forwardMove();
//							SysTick_Wait10ms(4);	 //3
//							rightMove();
//							SysTick_Wait10ms(2);   //1  
//							stepBack();
//							SysTick_Wait10ms(1);	 //1											
//							stop();																							
//						}
//						F_R_L_Sensor(); stop();
//						count++;
//					}
//					stop(); loopCount = 50;
//					count = 0; out = 0; stop();
//					SysTick_Wait10ms(100);     //wait					
//					l = 0;  turn = 0;
//				} */
//				//END turn LEFT
//				//turn RIGTH
//				else if(((distance0>30)&&(distance0<80)
//								&&(distance1>100)&&(distance1<500)
//								&&(distance2>20)&&(distance2<80)
//								&&(distance1>distance2))
//								||(r == 1)){//RIGHT TURN																	         
//					stop();	
//					GPIO_PORTF_DATA_R = 0x0E;	
//									
//          count = 0;									
//					while((count<10)&&(r==0)){
//						F_R_L_Sensor();
//						SysTick_Wait10ms(1); 
//						if (r==1)
//							GPIO_PORTF_DATA_R ^= 0x0E;	
//						else if (r==0)
//							GPIO_PORTF_DATA_R = 0x0E;	
//						count++;
//					}
//					count = 0;
//					
//					goTurn = 0;
//					if (((distance0<80)&&(distance1>100))||(r==1)) {
//						goTurn = 1;
//					}
//					if (goTurn==1) {
//						F_R_L_Sensor();
//						if (distance0<50) {
//							stepBack();
//							SysTick_Wait10ms(10);
//							stop();	
//            }
//            F_R_L_Sensor();
//            if (distance0>80) {
//							forwardMove();
//							SysTick_Wait10ms(5);
//							stop();	
//            }							
//						SysTick_Wait10ms(30);  //wait
//						//one time turn RIGHT
//						GPIO_PORTB_DATA_R &= ~0x01; //MotorA, backward	
//						GPIO_PORTB_DATA_R |= 0x02;  //MotorB, foward
//						PWM0A_Duty(39000);   			  //40,000 == 100%		
//						PWM0B_Duty(500);		        //40,000 == 100%
//						SysTick_Wait10ms(19);    							
//						stop();	
//						SysTick_Wait10ms(30);      //wait
//            turnLeft=0; turnRight++;						
//						//END turn Right		
//					}
//					goTurn = 0;					
//					count = 0;	out = 0; F_R_L_Sensor();
//					while((count<50)&&(out==0)){		
//						if (distance0<50) out = 1;
//						if ((distance1>100)&&(distance2<100)){
//							if((distance0>50)&&(distance2<50)){
//								GPIO_PORTF_DATA_R = 0x0C;
//								rightMove();
//								SysTick_Wait10ms(2);    //2
//								forwardMove();
//								SysTick_Wait10ms(4);	  //3
//								leftMove();
//								SysTick_Wait10ms(2);    //2
//								stepBack();
//								SysTick_Wait10ms(1);		//1		
//								stop();											 							
//							}
//							else if ((distance0>50)&&(distance2>50)){	 
//								GPIO_PORTF_DATA_R = 0x0A;											 
//								leftMove();
//								SysTick_Wait10ms(3);   //2
//								forwardMove();
//								SysTick_Wait10ms(4);	 //3
//								rightMove();
//								SysTick_Wait10ms(2);   //1  
//								stepBack();
//								SysTick_Wait10ms(1);	 //1											
//								stop();											 
//							}
//						}	
//            else if ((distance0>50)&&(distance1<100)
//							       &&(distance2<100)) {
//							GPIO_PORTF_DATA_R = 0x0E;								
//							moveStraight();
//            }							
//            else if ((distance2>100)&&(distance1<80)) {
//              if ((distance0>50)&&(distance1>50)) {
//								GPIO_PORTF_DATA_R = 0x0C;
//								rightMove();
//								SysTick_Wait10ms(2);    //2
//								forwardMove();
//								SysTick_Wait10ms(4);	  //3
//								leftMove();
//								SysTick_Wait10ms(2);    //2
//								stepBack();
//								SysTick_Wait10ms(1);		//1		
//								stop();											 
//              }		
//							else if ((distance0>50)&&(distance1<50)){	
//								GPIO_PORTF_DATA_R = 0x0A;											 
//								leftMove();
//								SysTick_Wait10ms(3);   //2
//								forwardMove();
//								SysTick_Wait10ms(4);	 //3
//								rightMove();
//								SysTick_Wait10ms(2);   //1  
//								stepBack();
//								SysTick_Wait10ms(1);	 //1											
//								stop();											 
//						  }							
//            }
//						else if ((distance0>50)&&(distance1>100)
//							       &&(distance2>100)) {
//							rightMove();
//							SysTick_Wait10ms(2);    //2
//							forwardMove();
//							SysTick_Wait10ms(4);	  //3
//							leftMove();
//							SysTick_Wait10ms(2);    //2
//							stepBack();
//							SysTick_Wait10ms(1);		//1		
//							stop();		
//							leftMove();
//							SysTick_Wait10ms(3);   //2
//							forwardMove();
//							SysTick_Wait10ms(4);	 //3
//							rightMove();
//							SysTick_Wait10ms(2);   //1  
//							stepBack();
//							SysTick_Wait10ms(1);	 //1											
//							stop();																
//						}
//						F_R_L_Sensor();
//						count++;
//					}
//					stop(); SysTick_Wait10ms(100);     //wait
//          count = 0;	out = 0; F_R_L_Sensor();				
//					while((count<10)&&(out==0)){  //PID 15
//						if (distance0>50) {
//							moveStraight();
//							SysTick_Wait10ms(2);
//						}						
//						if ((distance1>100)&&(distance2<100)){
//							if((distance0>50)&&(distance2<50)){
//								GPIO_PORTF_DATA_R = 0x0C; //rightMove();
//								distance1 = 60;
//                myPIDcontrol (Kp, Ki, Kd);																
//							}
//							else if ((distance0>50)&&(distance2>50)){	 
//								GPIO_PORTF_DATA_R = 0x0A;//leftMove();									 
//								distance1 = 40;
//                myPIDcontrol (Kp, Ki, Kd);								
//							}
//						}	
//            else if ((distance0>50)&&(distance1<100)
//							       &&(distance2<100)) {
//							GPIO_PORTF_DATA_R = 0x0E;								
//							moveStraight();
//            }							
//            else if ((distance2>100)&&(distance1<80)) {
//              if ((distance0>50)&&(distance1>50)) {
//								GPIO_PORTF_DATA_R = 0x0C; //rightMove();
//								distance2 = 40;
//								myPIDcontrol (Kp, Ki, Kd);								
//              }		
//							else if ((distance0>50)&&(distance1<50)){	
//								GPIO_PORTF_DATA_R = 0x0A; //leftMove();								 	
//								distance2 = 60;
//								myPIDcontrol (Kp, Ki, Kd);
//						  }							
//            }
//						else if ((distance0>50)&&(distance1>100)
//							       &&(distance2>100)) {
//							rightMove();
//							SysTick_Wait10ms(2);    //2
//							forwardMove();
//							SysTick_Wait10ms(4);	  //3
//							leftMove();
//							SysTick_Wait10ms(2);    //2
//							stepBack();
//							SysTick_Wait10ms(1);		//1		
//							stop();		
//							leftMove();
//							SysTick_Wait10ms(3);   //2
//							forwardMove();
//							SysTick_Wait10ms(4);	 //3
//							rightMove();
//							SysTick_Wait10ms(2);   //1  
//							stepBack();
//							SysTick_Wait10ms(1);	 //1											
//							stop();																
//						}
//						F_R_L_Sensor();
//						if (distance0<50) out =1;						
//						GPIO_PORTF_DATA_R = 0x04;
//						count++;
//					}
//					stop(); loopCount=0; 
//					count = 0; out = 0; 
//					SysTick_Wait10ms(50);     //wait	
//					turn = 0; r = 0;
//				}//END turnRIGTH	

//				//turn LEFT
//				else if (((distance0>30)&&(distance0<80)
//								 &&(distance1>20)&&(distance1<80)
//								 &&(distance2>100)&&(distance2<500)
//								 &&(distance2>distance1))
//								 ||(l == 1)){//LEFT TURN										 
//          stop();		 
//					GPIO_PORTF_DATA_R = 0x06;							
//					 
//					count = 0;
//					while(count<10){
//						SysTick_Wait10ms(1); 
//						if (l==1)
//							GPIO_PORTF_DATA_R ^= 0x06;	
//						else if (l==0)
//							GPIO_PORTF_DATA_R = 0x06;	
//						count++;
//					}
//					count = 0;
//					
//					F_R_L_Sensor();
//					if (distance0<50) {
//						stepBack();
//						SysTick_Wait10ms(10);
//						stop();	
//					}
//					F_R_L_Sensor();
//					if (distance0>80) {
//						forwardMove();
//						SysTick_Wait10ms(5);
//						stop();	
//					}
//					
//					SysTick_Wait10ms(30);     //wait	
//					//one time turn LEFT
//					GPIO_PORTB_DATA_R |= 0x01; //MotorA, forward
//					GPIO_PORTB_DATA_R &= ~0x02;//MotorB, backward
//					PWM0A_Duty(500);   			   //40,000 == 100%		
//					PWM0B_Duty(39000);		     //40,000 == 100%
//					SysTick_Wait10ms(20);    							
//					stop();	
//					SysTick_Wait10ms(30);     //wait	
//					//END turn LEFT		
//					
//					turnLeft++; turnRight=0;
//          count = 0;	out = 0; F_R_L_Sensor();			
//					while((count<50)&&(out==0)){					
//						if (distance0<50) out = 1;
//						if ((distance2>100)&&(distance1<80)){
//							if(distance1<50){
//								GPIO_PORTF_DATA_R = 0x0A;											 
//								leftMove();
//								SysTick_Wait10ms(3);   //2
//								forwardMove();
//								SysTick_Wait10ms(4);	 //3
//								rightMove();
//								SysTick_Wait10ms(2);   //1  
//								stepBack();
//								SysTick_Wait10ms(1);	 //1											
//								stop();											 														
//							}
//							else if (distance1>50){	 
//								GPIO_PORTF_DATA_R = 0x0C;
//								rightMove();
//								SysTick_Wait10ms(2);    //2
//								forwardMove();
//								SysTick_Wait10ms(4);	  //3
//								leftMove();
//								SysTick_Wait10ms(2);    //2
//								stepBack();
//								SysTick_Wait10ms(1);		//1		
//								stop();											 								
//							}
//						}	
//            else if ((distance1<100)&&(distance2<100)) {
//							GPIO_PORTF_DATA_R = 0x06;								
//							moveStraight();
//            }							
//            else if ((distance1>100)&&(distance2<80)) {
//              if (distance2>50) {
//								GPIO_PORTF_DATA_R = 0x0A;											 
//								leftMove();
//								SysTick_Wait10ms(3);   //2
//								forwardMove();
//								SysTick_Wait10ms(4);	 //3
//								rightMove();
//								SysTick_Wait10ms(2);   //1  
//								stepBack();
//								SysTick_Wait10ms(1);	 //1											
//								stop();											 								
//              }		
//							else if (distance2<50){	
//								GPIO_PORTF_DATA_R = 0x0C;
//								rightMove();
//								SysTick_Wait10ms(2);    //2
//								forwardMove();
//								SysTick_Wait10ms(4);	  //3
//								leftMove();
//								SysTick_Wait10ms(2);    //2
//								stepBack();
//								SysTick_Wait10ms(1);		//1		
//								stop();											 																
//						  }							
//            }
//						else if ((distance0>50)&&(distance1>100)
//							       &&(distance2>100)) {
//							GPIO_PORTF_DATA_R = 0x0C;
//							rightMove();
//							SysTick_Wait10ms(2);    //2
//							forwardMove();
//							SysTick_Wait10ms(4);	  //3
//							leftMove();
//							SysTick_Wait10ms(2);    //2
//							stepBack();
//							SysTick_Wait10ms(1);		//1		
//							stop();	
//              GPIO_PORTF_DATA_R = 0x0A;											 
//							leftMove();
//							SysTick_Wait10ms(3);   //2
//							forwardMove();
//							SysTick_Wait10ms(4);	 //3
//							rightMove();
//							SysTick_Wait10ms(2);   //1  
//							stepBack();
//							SysTick_Wait10ms(1);	 //1											
//							stop();																							
//						}
//						F_R_L_Sensor(); count++;
//					}
//					stop(); SysTick_Wait10ms(100);     //wait
//					count = 0; out = 0; F_R_L_Sensor();
//					while((count<10)&&(out==0)){	//PID 15
//						if (distance0>50) {
//							moveStraight();
//							SysTick_Wait10ms(2);
//						}						
//						if ((distance2>100)&&(distance1<80)){
//							if(distance1<50){
//								GPIO_PORTF_DATA_R = 0x0A;//leftMove();											 
//									distance2 = 60;
//								  myPIDcontrol (Kp, Ki, Kd);
//							}
//							else if (distance1>50){	 
//								GPIO_PORTF_DATA_R = 0x0C; //rightMove();
//									distance2 = 40;
//									myPIDcontrol (Kp, Ki, Kd);
//							}
//						}	
//            else if ((distance1<100)&&(distance2<100)) {
//							GPIO_PORTF_DATA_R = 0x06;								
//							moveStraight();
//            }							
//            else if ((distance1>100)&&(distance2<80)) {
//              if (distance2>50) {
//								GPIO_PORTF_DATA_R = 0x0A;//leftMove();											 
//								distance1 = 40;
//								myPIDcontrol (Kp, Ki, Kd);
//              }		
//							else if (distance2<50){	
//								GPIO_PORTF_DATA_R = 0x0C; //rightMove();
//								distance1 = 60;
//								myPIDcontrol (Kp, Ki, Kd);
//						  }							
//            }
//						else if ((distance0>50)&&(distance1>100)
//							       &&(distance2>100)) {
//							GPIO_PORTF_DATA_R = 0x0C;
//							rightMove();
//							SysTick_Wait10ms(2);    //2
//							forwardMove();
//							SysTick_Wait10ms(4);	  //3
//							leftMove();
//							SysTick_Wait10ms(2);    //2
//							stepBack();
//							SysTick_Wait10ms(1);		//1		
//							stop();	
//              GPIO_PORTF_DATA_R = 0x0A;											 
//							leftMove();
//							SysTick_Wait10ms(3);   //2
//							forwardMove();
//							SysTick_Wait10ms(4);	 //3
//							rightMove();
//							SysTick_Wait10ms(2);   //1  
//							stepBack();
//							SysTick_Wait10ms(1);	 //1											
//							stop();																							
//						}
//						F_R_L_Sensor();
//						if (distance0<50) out =1;						
//						GPIO_PORTF_DATA_R = 0x04;
//						count++;
//					}
//					stop(); loopCount = 80; 
//					count = 0; out = 0; stop();
//					SysTick_Wait10ms(50);     //wait					
//					l = 0;  turn = 0;
//				}//END turn LEFT				
//				//stirr Left***********************************************
///*				else if ((distance0>80)&&(distance1<80)
//									&&(distance2<80)&&(distance2>distance1)
//									&&(distance2-distance1>10)) {
//					GPIO_PORTF_DATA_R = 0x08;			//GREEN led
//					turnLeft=0; turnRight=0;	
//										 				 
//					if ((distance2>distance1)&&(distance2-distance1>10)){
//						pDistn0 = distance0; out = 0;
//						while(((distance0>80)&&(distance1<50)&&(out==0)) //40
//									||((distance0>80)&&(distance2>70)&&(out==0))) { //70
//							leftMove();
//							SysTick_Wait10ms(2);   //2
//							forwardMove();
//							SysTick_Wait10ms(3);	 //2
//							rightMove();
//							SysTick_Wait10ms(1);   //1  
//							stepBack();
//							SysTick_Wait10ms(1);	 //1											
//							stop();											 
//							F_R_L_Sensor();	
//							if(distance2>150) {
//								out = 1;
//							}
//							if ((distance2>70)||(distance1>70)) {
//								while((distance1>70)&&(distance1<150)
//									     &&(distance2<150)) {
//									rightMove();
//									F_R_L_Sensor();
//								}
//								stop();
//								F_R_L_Sensor();
//							}	
//						}
//						out = 0;
//					}
//					turn = 0;
//					F_R_L_Sensor();
//          rightMove();
//					SysTick_Wait10ms(1);  //3
//					stop();							
//				}
//        //END of stirr Left***************************************
//			 //stirr RIGTH***********************************************
//				else if ((distance0>80)&&(distance1<80)
//					         &&(distance2<80)&&(distance1>distance2)
//					         &&(distance1-distance2>10)) {
//					GPIO_PORTF_DATA_R = 0x0C;	//CYAN led
//          turnLeft=0; turnRight=0;		 

//					if ((distance1>distance2)&&(distance1-distance2>10)){
//						pDistn0 = distance0;
//						out = 0;
//						while(((distance0>80)&&(distance2<50)&&(out==0))  //40
//									||((distance0>80)&&(distance1>70)&&(out==0))) { //70
//							rightMove();
//							SysTick_Wait10ms(1);    //2
//							forwardMove();
//							SysTick_Wait10ms(3);	  //2
//							leftMove();
//							SysTick_Wait10ms(1);    //1
//							stepBack();
//							SysTick_Wait10ms(1);		//1		
//							stop();											 
//							F_R_L_Sensor();	
//							if (distance1>150) {
//								out = 1;
//              } 

//							if ((distance1>70)||(distance2>70)) {
//								while((distance2>70)&&(distance2<150)
//									    &&(distance1<150)) {
//									leftMove();
//									F_R_L_Sensor();
//								}
//								stop();
//								F_R_L_Sensor();
//							}
//						}
//						out = 0;
//					}
//					turn = 0;
//					F_R_L_Sensor();					
//          leftMove();
//					SysTick_Wait10ms(2);  //3
//					stop();
//					turn = 0;
//				}  	
//*/
//				//move FORWARD				
//				else if (f==1) { //PID
//					GPIO_PORTF_DATA_R = 0x08;	
//					SysTick_Wait10ms(100);
//					
//          count = 0;	out = 0;								
//					while((count<25)&&(out==0)){ 
//						if (distance0>70) {
//							moveStraight();
//							SysTick_Wait10ms(2);							
//						}
//						if ((distance0>50)&&(distance1<100)) {
//              distance2 = 110;							
//              myPIDcontrol (Kp, Ki, Kd);	
//							F_R_L_Sensor();
//						}
//						if ((distance0>50)&&(distance2<100)){
//							distance1 = 110;
//              myPIDcontrol (Kp, Ki, Kd);														
//						}
//						F_R_L_Sensor();	count++;
//						if (distance0<50)
//							out =1;
//					}
//					GPIO_PORTF_DATA_R = 0x04;
//					stop(); 
//					SysTick_Wait10ms(50);
//					count = 0; out = 0; stop();					
//					f = 0; turn = 0;
//					loopCount = 0;
//			  }	
///*				else if (f==1) {
//					GPIO_PORTF_DATA_R = 0x08;	
//					SysTick_Wait10ms(50);
//					
//          count = 0;	out = 0;								
//					while((count<100)&&(out==0)){ 
//						moveStraight();
//						SysTick_Wait10ms(1);
//						stop();
//						count++;
//						F_R_L_Sensor();
//						if (distance0<50)
//							out =1;
//						if ((distance0>50)&&(distance1<60)) {
//							leftMove();
//							SysTick_Wait10ms(3);   //2
//							forwardMove();
//							SysTick_Wait10ms(4);	 //2
//							rightMove();
//							SysTick_Wait10ms(2);   //1  
//							stepBack();
//							SysTick_Wait10ms(1);	 //1											
//							stop();											 
//							F_R_L_Sensor();							
//						}
//						if ((distance0>50)&&(distance2<60)){
//							rightMove();
//							SysTick_Wait10ms(2);    //2
//							forwardMove();
//							SysTick_Wait10ms(4);	  //2
//							leftMove();
//							SysTick_Wait10ms(2);    //1
//							stepBack();
//							SysTick_Wait10ms(1);		//1		
//							stop();											 
//							F_R_L_Sensor();							
//						}
//					}
//					count = 0; out = 0; stop();					
//					f = 0; turn = 0;
//			  }	*/

//////&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&		
//////PID Control				
//				else if ((distance0>50)&&(distance1-distance2!=0)
//					       &&(distance1<150)&&(distance2<150)) {
////					Ep = setPoint - (distance1-distance2); 
////					Ep = Ep;
////					Ed = Ep - lastError;
////					if ((Ep>-5)&&(Ep<5)) Ei = Ei + Ep;
////					if (Ep==0) {
////						Ei = 0; Ed = 0;
////					}
////					if(Ep>0) GPIO_PORTF_DATA_R = 0x08;
////					else if (Ep<0) GPIO_PORTF_DATA_R = 0x0C;
////					lastError = Ep;
////					speedA = speedA - (Ep)*(Kp) - (Ed)*(Kd);
////					speedB = speedB + (Ep)*(Kp) + (Ed)*(Kd);
////					if (speedA>39000) speedA=39000; //40,000 == 100%
////					if (speedB<100)  speedB=100;    //40,000 == 100%
////					if (speedB>39000) speedB=39000; //40,000 == 100%
////					if (speedA<100)  speedA=100;    //40,000 == 100%
////					motorA(speedA);
////					motorB(speedB);
//					myPIDcontrol (Kp, Ki, Kd);
//					loopCount++;
//				}			
//				if (loopCount==180) {
//					loopCount=0;
//					stop(); 
//					SysTick_Wait10ms(100);
//					GPIO_PORTF_DATA_R = 0x00;
//          loopCount=0;	          				
//				}			
//			}////END of whiel(turn == 0)					
//			//not keep the intersection
//			if ((deadEnd == 1)&&(goal == 0)){ 
//				turn = 'U';
//			}	
//      //save the intersection to array			
//      else if ((deadEnd == 0)&&(goal == 0)){ 			
//				if (turn == 0x03){////***turn RF == 0x03	    
//					travalArray[index++] = 0x03;
//					travalArray[index++] = 'R';
//					travalArray[index++] = 'F';
//					turn = 'F';
//					f = 1;
//					turn = 0; 
//				}	     											
//				else if (turn == 0x05) {/////***turn LF ==0x05	 
//					travalArray[index++] = 0x05;
//					travalArray[index++] = 'L';
//					travalArray[index++] = 'F';
//					turn = 'F';
//					f = 1;
//					turn = 0; 
//				}	      				
//				else if (turn == 0x06) {/////***turn LR == 0x06 
//					travalArray[index++] = 0x06;
//					travalArray[index++] = 'L';
//					travalArray[index++] = 'R';
//					turn = 'R';					
//					r = 1;    
//					turn = 0; 
//				}									
//				else if (turn == 0x07) {/////***LRF == 0x07 
//					travalArray[index++] = 0x07;
//					travalArray[index++] = 'L';
//					travalArray[index++] = 'R';
//					travalArray[index++] = 'F';
//					turn = 'F';
//					f = 1;
//					turn = 0;
//				}			
//			}
//		}//END OF:"while(turn!='U')";
//		if (goal == 0){				
//			while (turn == 'U'){
//				deadEnd=0; 
//				DFS_1stRun = 'U';  			
//				for (i=0; i<4; i++)
//					arrayTurns[i] = 0;	     				
//				i = 0;				
//				//array that hold the turns:0x03,0x05,0x06,0x07
//        if ((travalArray[index]) == 0)
//					index--;				
//				/*////pop off the TOP stack and save values to array[4];
//				////0x07==LRF-->[0]=='F', [1]=='R', [2]=='L',[3]==0x07 
//				////0x06==LR--->[0]=='R', [1]=='L', [2]== 0, [3]==0x06 
//				////0x05==LF--->[0]=='F', [1]=='L', [2]== 0, [3]==0x05 
//				////0x03=RF---->[0]=='F', [1]=='R', [2]== 0, [3]==0x03*/
//				while (((DFS_1stRun>0x0F)&&(index>0))||
//					    ((DFS_1stRun>0x0F)&&(index==0))) {
//					DFS_1stRun = travalArray[index];	
//          travalArray[index--] = 0;
//					if (DFS_1stRun > 0x0F){
//						arrayTurns[i] = DFS_1stRun;	
//						i++;
//					}
//				}			
//				arrayTurns[3] = DFS_1stRun;					
//				////RF,LF=0x03,0x05
//				if ((arrayTurns[3] == 0x03)||(arrayTurns[3]==0x05)) {					
//					if ((arrayTurns[0]=='F')&&(arrayTurns[1]=='R')) {
//						deadEnd = 0;
//						turn = 'L';
//						index++;
//						travalArray[index++] = arrayTurns[3]; //push 0x03
//						travalArray[index++] = arrayTurns[1]; //push 'R'
//					}					
//					else if ((arrayTurns[0]=='F')&&(arrayTurns[1]=='L')){
//						deadEnd = 0;
//						turn = 'R';
//						index++;
//						travalArray[index++] = arrayTurns[3]; //push 0x05
//						travalArray[index++] = arrayTurns[1]; //push 'L'
//					}					
//				  /*////2ND TURN, deadEnd = 1;
//					////0x05==LF--->[0]=='L',[1]==0,[2]== 0,[3]==0x05 
//				  ////0x03=RF---->[0]=='R',[1]==0,[2]== 0,[3]==0x03 */
//					else if ((arrayTurns[0]=='R')||(arrayTurns[0]=='L')){
//					  deadEnd = 1;									 
//						if (arrayTurns[0]=='R')
//							turn = 'L';						
//						else if (arrayTurns[0]=='L')
//							turn = 'R';
//					}							
//				}//END OF: 0x03==RF, 0x05==LF
//				
//				////RL=0x06
//				else if (arrayTurns[3]==0x06) {						
//					if (arrayTurns[0]=='R') {
//						deadEnd = 0;
//						turn = 'F';
//						index++;
//						travalArray[index++] = arrayTurns[3]; //push 0x06
//						travalArray[index++] = arrayTurns[1]; //push 'L'
//					}					
//					else if (arrayTurns[0]=='L') {
//						deadEnd = 1;
//						turn = 'R';
//					}	
//				}//END OF: 0x06==LR
//				
//				////LRF=0x07
//				else if (arrayTurns[3]==0x07) {						
//					if (arrayTurns[0]=='F') {
//						deadEnd = 0;
//						turn = 'L';
//						index++;
//						travalArray[index++] = arrayTurns[3]; //push 0x07
//						travalArray[index++] = arrayTurns[2]; //push 'L'
//						travalArray[index++] = arrayTurns[1]; //push 'R'
//					}
//					else if (arrayTurns[0] == 'R') {
//						deadEnd = 0;
//						turn = 'F';
//						index++;
//						travalArray[index++] = arrayTurns[3]; //push 0x07
//						travalArray[index++] = arrayTurns[1]; //push 'L'
//					}
//					else if (arrayTurns[0]=='L') {
//						deadEnd = 1;	
//						turn = 'R';
//					}						
//				}//END OF: 0x07==LRF				
//				if (turn == 'R'){    
//					r = 1;
//					turn = 0;  //go back to while(turn==0)
//				}					
//				else if (turn == 'L'){
//					l = 1;
//					turn = 0; //go back to while(turn==0)
//				}				
//				else if (turn == 'F'){
//					f = 1;
//					turn = 0; //go back to while(turn==0)
//				}
//			}//END OF:"while(turn=='U')"	
//    }//END of if(goal==0)				
//		if (goal==1) {			
//			i = 0; ii = 0;
//			while (travalArray[i] != 0){
//				if ((i>0)&&(travalArray[i-1]>0x0F)&&
//					 (travalArray[i]>0x0F)) {
//					secndRunArray[ii-1] = travalArray[i];
//				}
//				else {
//					secndRunArray[ii] = travalArray[i];	
//					ii++;
//				}
//				i++; 
//			}
//			ii = 0;
//			while(secndRunArray[ii] != 0) {
//				UART_OutString("secndAry:");
//				if (secndRunArray[ii] == 70)
//					UART_OutString(" F");
//				else if (secndRunArray[ii] == 82)
//					UART_OutString(" R");
//				else if (secndRunArray[ii] == 76)
//					UART_OutString(" L");
//				else 
//					UART_OutUDec(secndRunArray[ii]);
//				OutCRLF();
//				ii++;
//			}
//			ii = (ii+1)/2;
//			OutCRLF();
//			UART_OutString("number of Turns secndArray: ");
//			UART_OutUDec(i);
//			UART_OutString("---");
//			UART_OutUDec(ii);
//			OutCRLF();
//			stop();
//			ii=0;
//			
//			//press sw2 2-time to get out loop
//			GPIO_PORTF_DATA_R = 0x00;
//			while(goal == 1){
//				GPIO_PORTF_DATA_R ^= 0x06; //led pink
//				SysTick_Wait10ms(50);
//				if (stp_intr==2)
//					goal = 2;
//			}
//			stp_intr = 0;
//		} //END OF if(goal==1)
//		stp_intr = 0;	
//		GPIO_PORTF_DATA_R = 0x00;
//		while(goal==3) {
//			stop();
//			GPIO_PORTF_DATA_R ^= 0x08; //led green
//			SysTick_Wait10ms(30);
//			if (stp_intr>0) {
//				goal = 0;
//				turn = 0;
//			}
//		}	
//	}//END OF while((goal == 0)||(goal==2)), 	
//}	
////END OF Main
//void motorA(unsigned long speedA) {
//	GPIO_PORTB_DATA_R |= 0x01; //MotorA, foward	
//	PWM0A_Duty(speedA);  //40,000 == 100% , 100, 2500, 5000
//}
//void motorB(unsigned long speedB) {
//	GPIO_PORTB_DATA_R |= 0x02; //MotorB, foward	
//	PWM0B_Duty(speedB);	 //40,000 == 100% , 3000,10000, 10000		
//}
//void myPIDcontrol (double Kpp, double Kii, double Kdd) {
//	unsigned long speedA=3000, speedB=5000;
//	unsigned char setPoint = 0;
//	signed long Ep=0, Ed=0, Ei=0, lastError=0;	
//	Ep = setPoint - (distance1-distance2); 
//	Ep = Ep;
//	Ed = Ep - lastError;
//	if ((Ep>-5)&&(Ep<5)) Ei = Ei + Ep;
//	if (Ep==0) {
//		Ei = 0; Ed = 0;
//	}
//	if(Ep>0) GPIO_PORTF_DATA_R = 0x08;
//	else if (Ep<0) GPIO_PORTF_DATA_R = 0x0C;
//	lastError = Ep;
//	speedA = speedA - (Ep)*(Kpp) - (Ed)*(Kdd);
//	speedB = speedB + (Ep)*(Kpp) + (Ed)*(Kdd);
//	if (speedA>39000) speedA=39000; //40,000 == 100%
//	if (speedB<100)  speedB=100;    //40,000 == 100%
//	if (speedB>39000) speedB=39000; //40,000 == 100%
//	if (speedA<100)  speedA=100;    //40,000 == 100%
//	motorA(speedA);
//	motorB(speedB);
//}
//void moveStraight(void) {
//  GPIO_PORTB_DATA_R |= 0x01; //MotorA, foward	
//	GPIO_PORTB_DATA_R |= 0x02; //MotorB, foward	
//	PWM0A_Duty(4000);   			 //40,000 == 100% , 8000
//	PWM0B_Duty(5000);		     //40,000 == 100% , 10000
//}
//void forwardMove(void) {
//	//move Forward	low PWM pulse
//	GPIO_PORTB_DATA_R |= 0x01; 	 //MotorA, foward
//	GPIO_PORTB_DATA_R |= 0x02;   //MotorB, foward
//	PWM0A_Duty(5000);   				 //40,000 == 100%	
//	PWM0B_Duty(5000);		      	 //40,000 == 100%		
//}
//void rightMove(void){
//		//stirr Right
//	GPIO_PORTB_DATA_R &= ~0x01;  //MotorA, backward	
//	GPIO_PORTB_DATA_R |= 0x02;   //MotorB, forward
//	PWM0A_Duty(35000);   				 //40,000 == 100%
//	PWM0B_Duty(5000);	
//}
//void leftMove(void) {
//	//stirr Left
//	GPIO_PORTB_DATA_R |= 0x01;   //MotorA, forward
//	GPIO_PORTB_DATA_R &= ~0x02;  //MotorB, backward
//	PWM0A_Duty(5000);   				 //40,000 == 100%
//	PWM0B_Duty(35000);	
//}
//void stepBack(void) {
//	//move Back	hight PWM pulse	
//	GPIO_PORTB_DATA_R &= ~0x01; //MotorA, backward	
//	GPIO_PORTB_DATA_R &= ~0x02; //MotorB, backward
//	PWM0A_Duty(35000);   				//40,000 == 100%	
//	PWM0B_Duty(35000);		      //40,000 == 100%	
//}
//void shiftRight(void) {	
//	//stirr Right
//	GPIO_PORTB_DATA_R &= ~0x01;  //MotorA, backward	
//	GPIO_PORTB_DATA_R |= 0x02;   //MotorB, forward
//	PWM0A_Duty(35000);   				 //40,000 == 100%
//	PWM0B_Duty(5000);		         //40,000 == 100%	
//	SysTick_Wait10ms(2);
//						
//	//move Forward	low PWM pulse
//	GPIO_PORTB_DATA_R |= 0x01; 	 //MotorA, foward
//	GPIO_PORTB_DATA_R |= 0x02;   //MotorB, foward
//	PWM0A_Duty(5000);   				 //40,000 == 100%	
//	PWM0B_Duty(5000);		      	 //40,000 == 100%	
//	SysTick_Wait10ms(5);	//2,5

//	//stirr Left
//	GPIO_PORTB_DATA_R |= 0x01;   //MotorA, forward
//	GPIO_PORTB_DATA_R &= ~0x02;  //MotorB, backward
//	PWM0A_Duty(5000);   				 //40,000 == 100%
//	PWM0B_Duty(35000);		       //40,000 == 100%	
//	SysTick_Wait10ms(1);
//	stop();
//}
//void shiftLeft(void) {
//	//stirr Left
//	GPIO_PORTB_DATA_R |= 0x01;   //MotorA, forward
//	GPIO_PORTB_DATA_R &= ~0x02;  //MotorB, backward
//	PWM0A_Duty(5000);   				 //40,000 == 100%
//	PWM0B_Duty(35000);		       //40,000 == 100%	
//	SysTick_Wait10ms(2);
//					
//	//move Forward	low PWM pulse
//	GPIO_PORTB_DATA_R |= 0x01; 	 //MotorA, foward
//	GPIO_PORTB_DATA_R |= 0x02;   //MotorB, foward
//	PWM0A_Duty(5000);   				 //40,000 == 100%	
//	PWM0B_Duty(5000);		      	 //40,000 == 100%	
//	SysTick_Wait10ms(5);	//2,5

//	//stirr Right
//	GPIO_PORTB_DATA_R &= ~0x01;  //MotorA, backward	
//	GPIO_PORTB_DATA_R |= 0x02;   //MotorB, forward
//	PWM0A_Duty(35000);   				 //40,000 == 100%
//	PWM0B_Duty(5000);		         //40,000 == 100%	
//	SysTick_Wait10ms(1);
//	stop();
//}
//void stop(void) {
//		GPIO_PORTB_DATA_R |= 0x01; 	//MotorA, foward	
//		GPIO_PORTB_DATA_R |= 0x02;  //MotorB, forward
//		PWM0A_Duty(35000);   				//10%	MotorA, foward
//		PWM0B_Duty(35000);		      //10%	MotorB, foward
//}
////Timer0 Port PE4-5, distance0
//void timer0FrontDistance0(unsigned long *distance0) {
//  unsigned long distn0 = 0;
//	while ((distn0 == 0)||(distn0>5000)||(distn0<15)) {
//		GPIO_PORTE_DATA_R &= ~0x20;						 //PE5, Trigger is low for 2us
//		SysTick_Wait2us(1);
//		GPIO_PORTE_DATA_R |= 0x20;    				 //PE5, Trigger is high for 10us
//		SysTick_Wait10us(1);
//		GPIO_PORTE_DATA_R &= ~0x20;   				 //PE5 is low
//		while ((GPIO_PORTE_DATA_R&0x10)==0);	 //PE4 input is low, Echo
//		while (GPIO_PORTE_DATA_R&0x10) {    	 //PE4 input is high, Echo
//			TIMER0_CTL_R = 0x00000001;        	 //enable TIMER0A
//		}	
//		TIMER0_ICR_R = TIMER_ICR_TATOCINT;     //acknowledge TIMER0A timeout
//		TIMER0_CTL_R = 0x00000000;             //disable TIMER0A
//		
//		distn0 = ((count0/2) * 0.0343)*10;     //in milimeters	
//		count0 = 0;//
//	}
//	*distance0 = distn0;
//}
////Timer1 Port PD2-3, distance1, Right
//void timer1RightDistance1_1(unsigned long *distance1) {
//	unsigned long distn1 = 0;
//	while ((distn1==0)||(distn1<15)||(distn1>5000)) {
//		GPIO_PORTD_DATA_R &= ~0x08;							//PD3 trigger is low for 2us
//		SysTick_Wait2us(1);
//		GPIO_PORTD_DATA_R |= 0x08;    					//PD3 trigger is high for 10us
//		SysTick_Wait10us(1);
//		GPIO_PORTD_DATA_R &= ~0x08;   					//PD3 is low
//		while ((GPIO_PORTD_DATA_R&0x04)==0);	  //PD2 echo input is low
//		while ((GPIO_PORTD_DATA_R&0x04)) {      //PD2 echo input is high
//			TIMER1_CTL_R = 0x00000001;        		//enable TIMER1A
//		}	
//		TIMER1_ICR_R = TIMER_ICR_TATOCINT;  		// acknowledge TIMER1A timeout
//		TIMER1_CTL_R = 0x00000000;          		// disable TIMER1A during setup
//		distn1 = ((count1/2) * 0.0343)*10; //in milimeters	//
//		count1 = 0;//
//	}
//	*distance1 = distn1;
//}
////Timer2 Port PE2-3, distance2 Left
//void timer2LeftDistance2_2(unsigned long *distance2) {
//	unsigned long distn2 = 0;
//	while ((distn2==0)||(distn2<15)||(distn2>5000)) {
//	//Timer2 Port PE2-3, distance2,2
//	GPIO_PORTE_DATA_R &= ~0x08;						  //PE3 trigger is low for 2us
//	SysTick_Wait2us(1);
//	GPIO_PORTE_DATA_R |= 0x08;    			    //PE3 trigger is high for 10us
//	SysTick_Wait10us(1);
//	GPIO_PORTE_DATA_R &= ~0x08;   			    //PE3 is low
//	while ((GPIO_PORTE_DATA_R&0x04)==0);    //PE2 echo input is low
//	while (GPIO_PORTE_DATA_R&0x04){         //PE2 echo input is high
//		TIMER2_CTL_R = 0x00000001;     	      //enable TIMER0A
//	}				
//	TIMER2_ICR_R = TIMER_ICR_TATOCINT;      //acknowledge TIMER2A timeout
//	TIMER2_CTL_R = 0x00000000;
//		distn2 = ((count2/2) * 0.0343)*10; //in milimeters	
//		count2 = 0;
//	}
//	*distance2 = distn2;	
//}

//void PortF_Init(void){ 
//	volatile unsigned long delay;
//  SYSCTL_RCGC2_R |= 0x20;         // (1) activate Port F
//  delay = SYSCTL_RCGC2_R;         // allow time for clock to stabilize
//  GPIO_PORTF_LOCK_R = 0x4C4F434B; // (2) unlock Port F lock
//  GPIO_PORTF_CR_R = 0x1F;         //    enable commit (allow configuration changes) on PF4-0
//  GPIO_PORTF_AMSEL_R = 0x00;      // (3) disable analog functionality on PF4-0
//  GPIO_PORTF_PCTL_R = 0x00000000; // (4) configure PF4-0 as GPIO
//	GPIO_PORTF_DIR_R &= ~0x10;      // (c) make PF4 in (built-in button)
//	GPIO_PORTF_DIR_R &= ~0x01;      // (c) make PF0 in (built-in button)
//  GPIO_PORTF_DIR_R |= 0x0E;       // (5) PF4 and PF0 in, PF3-1 out
//	GPIO_PORTF_DEN_R |= 0x01;       //    enable digital I/O on PF0 
//	GPIO_PORTF_DEN_R |= 0x10;       //    enable digital I/O on PF4 
//  GPIO_PORTF_DEN_R = 0x1F;        // (7) enable digital I/O on PF4-0
//  GPIO_PORTF_AFSEL_R = 0x00;      // (6) disable alt funct on PF4-0
//  GPIO_PORTF_PUR_R |= 0x11;     	//     enable weak pull-up on PF4,0
//  GPIO_PORTF_IS_R &= ~0x11;     	// (d) PF4,PF0 is edge-sensitive
//  GPIO_PORTF_IBE_R &= ~0x11;    	//     PF4,PF0 is not both edges
//  GPIO_PORTF_IEV_R &= ~0x11;    	//     PF4,PF0 falling edge event
//  GPIO_PORTF_ICR_R = 0x11;      	// (e) clear flags 4,0
//  GPIO_PORTF_IM_R |= 0x11;      	// (f) arm interrupt on PF4,PF0
//  NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00400000; // (g) priority 2
//  NVIC_EN0_R = 0x40000000;      	// (h) enable interrupt 30 in NVIC
//}

////PB6, PB7 is PWM, PB0, PB1 is Direction (PB6-->PB0, PB7-->PB1)
//void PortB_Init(void){
//	unsigned long volatile delay;
//	SYSCTL_RCGC2_R |= 0x02;           // 1) activate Port B
//  delay = SYSCTL_RCGC2_R;           // allow time for clock to stabilize
//  GPIO_PORTB_AMSEL_R &= ~0x03;      // 3) disable analog functionality on PB0, PB1
//  GPIO_PORTB_PCTL_R &= ~0x000000FF; // 4) configure PB0, PB1 as GPIO
//  GPIO_PORTB_DIR_R |= 0x03;         // 5) PB0, PB1 as output
//  GPIO_PORTB_AFSEL_R &= ~0x03;      // 6) disable alt funct on PB0, PB1
//  GPIO_PORTB_DEN_R |= 0x03;         // 7) enable digital I/O on PB0, PB1
//	
//	GPIO_PORTB_AMSEL_R = 0x00;        // 3) disable analog functionality on PB
//  GPIO_PORTB_PCTL_R &= ~0x00000F00; // 4) configure PB2 as GPIO
//  GPIO_PORTB_DIR_R |= 0x04;         // 5) PB2 as output
//  GPIO_PORTB_AFSEL_R &= ~0x04;      // 6) disable alt funct on PB
//  GPIO_PORTB_DEN_R |= 0x04;         // 7) enable digital I/O on PB
//}

//void PortC_Init(void){  
//	unsigned long volatile delay;
//  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOC; // activate port C
//  delay = SYSCTL_RCGC2_R;
//  GPIO_PORTC_DIR_R &= ~0x40;    	  		// make PC6 as input
//	GPIO_PORTC_DIR_R |= 0x80;         		// make PC7 as output
//  GPIO_PORTC_AFSEL_R &= ~0xC0;      		// disable alt funct on PC6-7
//  GPIO_PORTC_DEN_R |= 0xC0;         		// enable digital I/O on PC6-7
//  GPIO_PORTC_PCTL_R &= ~0xFF000000; 		// configure PC6-7 as GPIO
//  GPIO_PORTC_AMSEL_R &= ~0xC0;      		// disable analog functionality on PC6-7
//}

//void PortD_Init(void){  
//	unsigned long volatile delay;
//  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOD; // activate port D
//  delay = SYSCTL_RCGC2_R;
//  GPIO_PORTD_DIR_R &= ~0x04;    	  		// make PD2 as input
//	GPIO_PORTD_DIR_R |= 0x08;         		// make PD3 as output
//  GPIO_PORTD_AFSEL_R &= ~0x0C;      		// disable alt funct on PD2-3
//  GPIO_PORTD_DEN_R |= 0x0C;         		// enable digital I/O on PD2-3
//  GPIO_PORTD_PCTL_R &= ~0x0000FF00; 		// configure PD2-3 as GPIO
//  GPIO_PORTD_AMSEL_R &= ~0x0C;      		// disable analog functionality on PD2-3
//}

//void PortE_Init(void){  
//	unsigned long volatile delay;
//  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOE; // activate port E
//  delay = SYSCTL_RCGC2_R;
//  GPIO_PORTE_DIR_R &= ~0x04;    	  		// make PE2 as input
//	GPIO_PORTE_DIR_R |= 0x08;         		// make PE3 as output
//  GPIO_PORTE_AFSEL_R &= ~0x0C;      		// disable alt funct on PE2-3
//  GPIO_PORTE_DEN_R |= 0x0C;         		// enable digital I/O on PE2-3
//  GPIO_PORTE_PCTL_R &= ~0x0000FF00; 		// configure PE2-3 as GPIO
//  GPIO_PORTE_AMSEL_R &= ~0x0C;      		// disable analog functionality on PE2-3
//	
//  GPIO_PORTE_DIR_R &= ~0x10;    	  		// make PE4 as input
//	GPIO_PORTE_DIR_R |= 0x20;         		// make PE5 as output
//  GPIO_PORTE_AFSEL_R &= ~0x30;      		// disable alt funct on PE4-5
//  GPIO_PORTE_DEN_R |= 0x30;         		// enable digital I/O on PE4-5
//  GPIO_PORTE_PCTL_R &= ~0x00FF0000; 		// configure PE4-5 as GPIO
//  GPIO_PORTE_AMSEL_R &= ~0x30;      		// disable analog functionality on PE4-5
//}

//void PortA_Init(void){  
//	unsigned long volatile delay;
//  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA; // activate port A
//  delay = SYSCTL_RCGC2_R;
//  GPIO_PORTA_DIR_R &= ~0x04;    	  		// make PA2 as input
//	GPIO_PORTA_DIR_R |= 0x08;         		// make PA3 as output
//  GPIO_PORTA_AFSEL_R &= ~0x0C;      		// disable alt funct on PA2-3
//  GPIO_PORTA_DEN_R |= 0x0C;         		// enable digital I/O on PA2-3
//  GPIO_PORTA_PCTL_R &= ~0x0000FF00; 		// configure PA2-3 as GPIO
//  GPIO_PORTA_AMSEL_R &= ~0x0C;      		// disable analog functionality on PA2-3
//}

///*
//// Color    LED(s) PortF
//// dark     ---    0
//// red      R--    0x02
//// blue     --B    0x04
//// green    -G-    0x08
//// yellow   RG-    0x0A
//// sky blue -GB    0x0C
//// white    RGB    0x0E
//// pink     R-B    0x06
//*/



