#pragma
#include <exception>
#include "pixmap.h"
#include "stackll.h"

// fill function: use stack solution
bool fill(PixMap& image, const Pixel& fillColour, int x, int y) {
    
    bool result = false;
    
    //struct Point: use to store point that to be filled
    struct Point{
        int x;
        int y;
        Point(){
            x=0;
            y=0;
        }
        Point(int xx, int yy){
            x=xx;
            y=yy;
        }
    };
    
    //get image width, height and start point pixel
    // use them to check the point's validity
    int imageW = image.width();
    int imageH = image.height();
    Pixel originalPixel = image.getPixel(x, y);
    
    //declare a stack to store points that need to be filled
   Stack<Point> stack;
   
   //push first (start) point to the stack
   stack.push(Point(x,y));
   
   //use while loop to fill all point 
   while (!stack.isEmpty()) {
       
       //pop the top point in the stack, fill the fill color in the point
        Point p = stack.top();
        int X = p.x;
        int Y = p.y;

        stack.pop();
        image.setPixel(fillColour, X, Y);
        result = true;
        
        
        //4 ways check: the left, right, top and bottom point of the top point in the stack 
        // to see if they are connected by compare their color with start point color(originalPixel)

        if (X >= 0 && Y >= 0 && X < imageW && Y < imageH) {


            if (X + 1 >= 0 && Y >= 0 && (X + 1) < imageW && Y < imageH) {
                
                if ((image.getPixel(X + 1, Y)) == originalPixel)
                    stack.push(Point(X + 1, Y));
            }


            if (X - 1 >= 0 && Y >= 0 && X - 1 < imageW && Y < imageH) {
                
                if ((image.getPixel(X - 1, Y)) == originalPixel)
                    stack.push(Point(X - 1, Y));
            }



            if (X >= 0 && Y + 1 >= 0 && X < imageW && Y + 1 < imageH) {
                
                if ((image.getPixel(X, Y + 1)) == originalPixel)
                    stack.push(Point(X, Y + 1));
            }



            if (X >= 0 && Y - 1 >= 0 && X < imageW && Y - 1 < imageH) {
                
                if ((image.getPixel(X, Y-1)) == originalPixel)
                    stack.push(Point(X, Y - 1));
            }

        }
    }
   
   return result;
    
}
