// to compile/run:
//   javac Input.java
//   java Input
//
// Will create file 'Input.class'

import java.util.Scanner;

public class Input {
   
    public static void main (String [] args) {
	int num;
        Scanner s = new Scanner(System.in);
	System.out.print("enter an integer: ");
        num = s.nextInt();
        System.out.print("value entered: ");
        System.out.println(num);
    }

}
