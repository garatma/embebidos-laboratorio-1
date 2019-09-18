import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class SE_Lab_HostTempApp extends PApplet {


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


// Declaraciones para graficar funciones...
int cosVal;
int cantValues;
ScrollingFcnPlot f1,f2;

//Botones...
RectButton rectBtn1, rectBtn2;
PFont myFont;

//Etiquetas textuales...
boolean alert = false;
boolean prealert = false;
Label lbl1, lbl2, lbl3, lbl4, lbl5, lbl6, lbl7, lbl8, lbl9, lbl10, lbl11;
Label yVal1,yVal2,yVal3;

//Ventana y viewports...
int pgFunctionViewportWidth = 480;
int pgControlViewportWidth = 120;
int pgViewportsHeight = 240;

public void setup() {

  //Se define el tamaño de la ventana de la aplicación... 
  
  
  //Se inicializan los arreglos para almacenar las funciones...
  cantValues = pgFunctionViewportWidth;
  f1 = new ScrollingFcnPlot(cantValues,color(100,0,0),-1,1);
  f2 = new ScrollingFcnPlot(cantValues,color(0,100,0),0,height);
  
  //Se inicializan los botones...
  rectBtn1 = new RectButton(pgFunctionViewportWidth+10,10,60,40,color(102),color(50),color(255),"B1");
  rectBtn2 = new RectButton(pgFunctionViewportWidth+10,60,60,40,color(102),color(50),color(255),"B2");
  
  //Se inicializan los labels...
  lbl1 = new Label(pgFunctionViewportWidth+10,110,color(255),"Status: ");
  lbl2 = new Label(pgFunctionViewportWidth+60,110,color(255),"-");
  lbl3 = new Label(pgFunctionViewportWidth+10,130,color(255),"T.Actual: ");
  lbl4 = new Label(pgFunctionViewportWidth+70,130,color(255),"30ºC");
  lbl5 = new Label(pgFunctionViewportWidth+10,150,color(255),"T.Max: ");
  lbl6 = new Label(pgFunctionViewportWidth+70,150,color(255),"30ºC");
  lbl7 = new Label(pgFunctionViewportWidth+10,170,color(255),"T.Min: ");
  lbl8 = new Label(pgFunctionViewportWidth+70,170,color(255),"30ºC");
  lbl9 = new Label(pgFunctionViewportWidth+10,190,color(255),"T.Prom: ");
  lbl10 = new Label(pgFunctionViewportWidth+70,190,color(255),"30ºC");
  lbl11 = new Label(pgFunctionViewportWidth+10,210,color(255,0,0),"ALERTA!!!");
  
  yVal1 = new Label(10,5,color(255),"+1");
  yVal2 = new Label(10,(pgViewportsHeight-20)/2,color(255),"0");
  yVal3 = new Label(10,pgViewportsHeight-25,color(255),"-1");
  
  //Inicializa el font de la GUI...
  myFont = createFont("FFScala", 14);
  textFont(myFont);
  
}

public void draw() {

  
  //Se actualizan las funciones de ejemplo (f1: coseno(x), f2: función que depende de la posición Y del mouse)
  float amount = map(cosVal, 0, cantValues, 0, 2*PI);
  f1.updateValue(cos(amount));
  f2.updateValue(height-mouseY);
  
  //Se incrementa el ángulo de la función coseno...
  cosVal = (cosVal + 1) % cantValues;
  
  //Permite expermientar con la velocidad de scroll al actualizar más lentamente los valores...
  //delay(50);
     
  //Rendering de la interface...
  background(125);
  stroke(0);
  noFill();
 
  //Dibuja las funciones...
  f1.displayIntoRect(30,10,pgFunctionViewportWidth-10,pgViewportsHeight-10);
  f2.displayIntoRect(30,10,pgFunctionViewportWidth-10,pgViewportsHeight-10);
  
  //Procesa eventos de MouseOver...
  rectBtn1.update();
  rectBtn2.update();
  
  //Procesa las entradas (botones)
  if(mousePressed) {
    if(rectBtn1.pressed()) {
      rectBtn1.currentcolor = color(0,100,0);
      lbl2.caption = "Btn1";
      prealert = true;
    } 
    else if(rectBtn2.pressed()) {
      rectBtn2.currentcolor = color(0,100,0);
      lbl2.caption = "Btn2";
      prealert = true;
    }
  }
  
  
  //Dibuja el eje X y el recuadro de los gráficos...
  stroke(0);
  line(30, pgViewportsHeight/2, pgFunctionViewportWidth-10, pgViewportsHeight/2);
  rect(30,10,pgFunctionViewportWidth-40,pgViewportsHeight-20);
  
  //Se dibujan los botones...
  rectBtn1.display();
  rectBtn2.display();
  
  //Se dibuja texto adicional...(labels, etc)
  lbl1.display();
  lbl2.display();
  lbl3.display();
  lbl4.display();
  lbl5.display();
  lbl6.display();
  lbl7.display();
  lbl8.display();
  lbl9.display();
  lbl10.display();

  if (alert) lbl11.display();
  
  yVal1.display();
  yVal2.display();
  yVal3.display();  
}

public void mouseReleased()
{
  //Si se pulsó algún botón y se completa el click, se hace el toggle sobre la etiqueta de alerta...
  if(prealert)
  {
    alert=!alert;
    prealert = false;
  }
}
/**
 * Clases que definen botones.
 * Se basan en el ejemplo Topics > GUI > Buttons de Processing 1.5.
 *
 * http://processing.org/learning/topics/buttons.html
 *
 */

class Button
{
  int x, y;
  int size, size2;
  int basecolor, highlightcolor;
  int currentcolor,textcolor;
  boolean over = false;
  boolean pressed = false;   
  boolean locked = false;
  String caption = "Button";

  public void update() 
  {
    if(over()) {
      currentcolor = highlightcolor;
    } 
    else {
      currentcolor = basecolor;
    }
  }

  public boolean pressed() 
  {
    if(over) {
      locked = true;
      return true;
    } 
    else {
      locked = false;
      return false;
    }    
  }

  public boolean over() 
  { 
    return true; 
  }

  public boolean overRect(int x, int y, int width, int height) 
  {
    if (mouseX >= x && mouseX <= x+width && 
      mouseY >= y && mouseY <= y+height) {
      return true;
    } 
    else {
      return false;
    }
  }

  public boolean overCircle(int x, int y, int diameter) 
  {
    float disX = x - mouseX;
    float disY = y - mouseY;
    if(sqrt(sq(disX) + sq(disY)) < diameter/2 ) {
      return true;
    } 
    else {
      return false;
    }
  }

}

class CircleButton extends Button
{ 
  CircleButton(int ix, int iy, int isize, int icolor, int ihighlight, int textcolor, String caption) 
  {
    x = ix;
    y = iy;
    size = isize;
    basecolor = icolor;
    highlightcolor = ihighlight;
    currentcolor = basecolor;
    this.textcolor = textcolor;
    this.caption = caption;
  }

  public boolean over() 
  {
    if( overCircle(x, y, size) ) {
      over = true;
      return true;
    } 
    else {
      over = false;
      return false;
    }
  }

  public void display() 
  {
    stroke(255);
    fill(currentcolor);
    ellipse(x, y, size, size);
    fill(textcolor);
    textAlign(CENTER,CENTER);
    text(caption, x+size/2, y+size/2);
  }
}

class RectButton extends Button
{
  RectButton(int ix, int iy, int isize, int isize2, int icolor, int ihighlight, int textcolor, String caption) 
  {
    x = ix;
    y = iy;
    size = isize;
    size2 = isize2;
    basecolor = icolor;
    highlightcolor = ihighlight;
    currentcolor = basecolor;
    this.textcolor = textcolor;
    this.caption = caption;
  }

  public boolean over() 
  {
    if( overRect(x, y, size, size2) ) {
      over = true;
      return true;
    } 
    else {
      over = false;
      return false;
    }
  }

  public void display() 
  {
    stroke(255);
    fill(currentcolor);
    rect(x, y, size, size2);
    fill(textcolor);
    textAlign(CENTER,CENTER);
    text(caption, x+size/2, y+size2/2);
  }
}
/**
 * Clase que define etiquetas textuales para la GUI de la aplicación.
 * Define una posición (esquina superior izquierda) para la etiqueta, el
 * contenido de la misma y el color para el renderizado del texto.

 */

class Label
{
  int x, y;
  int textcolor;
  String caption;

  Label(int x, int y, int textcolor, String caption)
  {
    this.x = x;
    this.y = y;
    this.textcolor = textcolor;
    this.caption = caption;
  }
  
  public void display() 
  {
    stroke(255);
    fill(textcolor);
    textAlign(LEFT,TOP);
    text(caption, x, y);
  }  
}
/**
 * Clase que define un graficador de funciones que hace scroll horizontal en el tiempo.
 * Permite definir un conjunto arbitrario de funciones y plotearlas en el mismo gráfico.
 * El scroll del gráfico es controlado por las modificaciones a los valores del mismo (si no
 * se producen actualizaciones en los valores de las funciones, el gráfico no se desplaza).

 */
 
class ScrollingFcnPlot
{
  float[] f;
  int colorF;
  int fPtr;
  int cantValues;
  boolean mustScroll = false;
  int maxVal, minVal;
  
  ScrollingFcnPlot (int cantValues, int colorF, int minVal, int maxVal)
  {
    this.f = new float[cantValues];
    this.fPtr = 0;
    this.cantValues = cantValues;
    this.colorF = colorF;
    this.maxVal = maxVal;
    this.minVal = minVal;    
  }
  
  public void updateValue(float value)
  {
    this.f[fPtr] = value;
    this.mustScroll = true;
      
    //Se incrementa el puntero circular
    fPtr = (fPtr + 1) % cantValues;
  }
  
  public void displayIntoRect(int x1,int y1,int x2,int y2)
  {
    if (mustScroll)
    {
      mustScroll = false;
      
      stroke(colorF);
      
      beginShape();
      for(int i = 0; i<f.length;i++){
        vertex(map(i,0,cantValues,x1,x2),map(f[(fPtr+i)%cantValues], minVal, maxVal, y2, y1));
      }
      endShape();
    }  
  }
}
  public void settings() {  size(800, 600); }
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "SE_Lab_HostTempApp" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
