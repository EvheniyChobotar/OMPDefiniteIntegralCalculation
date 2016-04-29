package mainPackage;

import java.util.ArrayList;

public class Main 
{
    public static ArrayList<Double> parellelTimeList    = new ArrayList<Double>();
    public static ArrayList<Double> sequentialTimeList  = new ArrayList<Double>();   
    public static ArrayList         dimensionList       = new ArrayList();
    private native double nativeDefiniteParallelIntegralCalculation(int a,int b, int n);
    private native double nativeDefiniteSequentialIntegralCalculation(int a,int b, int n);
    
    static
    {
        System.load("/home/eugenej/NetBeansProjects/OMPDefiniteIntegralCalculation/C-files/JNIDLforLabTwo/dist/libJNIForLabTwo.so");
    }
    
    public static void main(String[] args) 
    {
        
        calculate(); 
    }
    
    
    public static void calculate()
    {
        for(int i=100;i<=1000;i+=100)
        {  
           parellelTimeList.add( new Main().nativeDefiniteParallelIntegralCalculation(1,5,i));
           sequentialTimeList.add(new Main().nativeDefiniteSequentialIntegralCalculation(1,5,i));
           dimensionList.add(i);             
        }
        
        DrawGraphic draw = new DrawGraphic("Chobotar_OMPLabTwo");
        draw.pack();
        draw.setVisible(true); 
        parellelTimeList.clear();
        sequentialTimeList.clear();
        dimensionList.clear();        
    }
}
