
/**
 * Ejemplo de skecth Processing para el desarrollo del Laboratorio.
 *
 * Este skecth implementa un programa en el host que tiene la capacidad de
 * graficar funciones que evolucionan en el tiempo y además permite la
 * presentación de datos simples mediante Labels, y la captura de eventos
 * del usuario mediante la implementación de botones simples.
 *
 * La aplicación divide la ventana en 2 regiones, una de dibujado y otra 
 * donde se ubican los botones y etiquetas de información.
 *
 */
import processing.serial.*;

// Declaraciones para graficar funciones...
int cosVal;
int cantValues;
ScrollingFcnPlot factual, fmax, fmin, fprom;

Serial arduino;

int actual = 0,
	maximo = 0,
	minimo = 200,
	prom = 0,
	suma = 0,
	indice = 0,
	cantidad_censados = 0,
	modo = 1,
	cuenta = 0;

int [] muestras = new int[60];

//Botones...
RectButton boton_actual, boton_max, boton_min, boton_prom;
PFont myFont;

//Etiquetas textuales...
boolean alert = false;
boolean prealert = false;
Label label_texto_actual, label_temperatura_actual, 
	  label_texto_max, label_temperatura_max, 
	  label_texto_min, label_temperatura_min, 
	  label_texto_prom, label_temperatura_prom; 
Label yVal1,yVal2,yVal3;

//Ventana y viewports...
int pgFunctionViewportWidth = 480;
int pgControlViewportWidth = 120;
int pgViewportsHeight = 240;

void setup() 
{

  	//Se define el tamaño de la ventana de la aplicación... 
  	size(660, 240);
  	
  	//Se inicializan los arreglos para almacenar las funciones...
  	cantValues = pgFunctionViewportWidth;
  	factual = new ScrollingFcnPlot(cantValues,color(100,0,0),-1,1);
  	fmax = 	new ScrollingFcnPlot(cantValues,color(0,100,0),-1,1);
  	fmin = 	new ScrollingFcnPlot(cantValues,color(0,0,100),-1,1); 
  	fprom = 	new ScrollingFcnPlot(cantValues,color(100,100,100),-1,1);

  	//Se inicializan los botones...
  	boton_actual = new RectButton(pgFunctionViewportWidth+10,10,60,40,color(102),color(50),color(255),"Actual");
  	boton_max = new	RectButton(pgFunctionViewportWidth+10,60,60,40,color(102),color(50),color(255),"Max");
   	boton_min = new	RectButton(pgFunctionViewportWidth+100,10,60,40,color(102),color(50),color(255),"Min"); 	
  	boton_prom = new RectButton(pgFunctionViewportWidth+100,60,60,40,color(102),color(50),color(255),"Prom");

	//Se inicializan los labels...
  	label_texto_actual = new Label(pgFunctionViewportWidth+10,130,color(255),"T.Actual: ");
  	label_temperatura_actual = new Label(pgFunctionViewportWidth+75,130,color(255),"-");
  	label_texto_max = new Label(pgFunctionViewportWidth+10,150,color(255),"T.Max: ");
  	label_temperatura_max = new	Label(pgFunctionViewportWidth+75,150,color(255),"-");
  	label_texto_min = new Label(pgFunctionViewportWidth+10,170,color(255),"T.Min: ");
  	label_temperatura_min = new Label(pgFunctionViewportWidth+75,170,color(255),"-");
  	label_texto_prom = new Label(pgFunctionViewportWidth+10,190,color(255),"T.Prom: ");
  	label_temperatura_prom = new Label(pgFunctionViewportWidth+75,190,color(255),"-");
  	
  	yVal1 = new Label(10,5,color(255),"+1");
  	yVal2 = new Label(10,(pgViewportsHeight-20)/2,color(255),"0");
  	yVal3 = new Label(10,pgViewportsHeight-25,color(255),"-1");
  	
  	//Inicializa el font de la GUI...
  	myFont = createFont("FFScala", 14);
  	textFont(myFont);

	arduino = new Serial(this,Serial.list()[0],9600);
	arduino.buffer(2);
}

void draw() 
{
  	//Se actualizan las funciones de ejemplo (f1: coseno(x), f2: función que depende de la posición Y del mouse)
  	float amount = map(cosVal, 0, cantValues, 0, 2*PI);
  	factual.updateValue(cos(amount));
  	fmax.updateValue(height-mouseY);
  	fmin.updateValue(sin(amount));
  	fprom.updateValue(tan(amount));
  	
  	//Se incrementa el ángulo de la función coseno...
  	cosVal = (cosVal + 1) % cantValues;
  	
  	//Permite expermientar con la velocidad de scroll al actualizar más lentamente los valores...
  	//delay(50);
  	   
  	//Rendering de la interface...
  	background(125);
  	stroke(0);
  	noFill();
 
  	//Dibuja las funciones...
  	factual.displayIntoRect(30,10,pgFunctionViewportWidth-10,pgViewportsHeight-10);
  	fmax.displayIntoRect(30,10,pgFunctionViewportWidth-10,pgViewportsHeight-10);
  	fmin.displayIntoRect(30,10,pgFunctionViewportWidth-10,pgViewportsHeight-10);
  	fprom.displayIntoRect(30,10,pgFunctionViewportWidth-10,pgViewportsHeight-10);

  	//Procesa eventos de MouseOver...
  	boton_actual.update();
  	boton_max.update();
  	boton_min.update();
  	boton_prom.update();

	//Procesa las entradas (botones)
  	if(mousePressed) 
	{
  	  	if(boton_actual.pressed()) 
		{
			arduino.write('1');
			boton_actual.currentcolor = color(0,100,0);
		}
  	  	else if(boton_max.pressed()) 
		{
			arduino.write('2');
			boton_max.currentcolor = color(0,100,0);
		}
  		else if(boton_min.pressed())
		{
			arduino.write('3');
			boton_min.currentcolor = color(0,100,0);
		}
  		else if(boton_prom.pressed())
		{
			arduino.write('4');
			boton_prom.currentcolor = color(0,100,0);
		}
  	}

  	
  	//Dibuja el eje X y el recuadro de los gráficos...
  	stroke(0);
  	line(30, pgViewportsHeight/2, pgFunctionViewportWidth-10, pgViewportsHeight/2);
  	rect(30,10,pgFunctionViewportWidth-40,pgViewportsHeight-20);
  	
  	//Se dibujan los botones...
  	boton_actual.display();
  	boton_max.display();
  	boton_min.display();
  	boton_prom.display();
  	
  	//Se dibuja texto adicional...(labels, etc)
  	label_texto_actual.display();
  	label_temperatura_actual.display();
  	label_texto_max.display();
  	label_temperatura_max.display();
  	label_texto_min.display();
  	label_temperatura_min.display();
  	label_texto_prom.display();
  	label_temperatura_prom.display();

  	yVal1.display();
  	yVal2.display();
  	yVal3.display();  
}

void serialEvent(Serial p)
{
	String actual_string = p.readString();
	if ( cuenta > 5 )
	{
		actual = int(actual_string);
		if ( actual < minimo ) minimo = actual;
		else if ( actual > maximo ) maximo = actual;
		
		if ( cantidad_censados < 60 )
			cantidad_censados++;
		else
			suma -= muestras[indice];

		muestras[indice] = actual;
		suma += actual;
		prom = (int) suma/cantidad_censados;

		indice++;
		if ( indice == 60 )
			indice = 0;

		label_temperatura_actual.setCaption(str(actual));
		label_temperatura_max.setCaption(str(maximo));
		label_temperatura_min.setCaption(str(minimo));
		label_temperatura_prom.setCaption(str(prom));
	}
	else
		cuenta++;
}
