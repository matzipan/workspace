 public class ThreadScheduling3 extends Thread {
        private static class Pair {
          int x = 0;
          int y = 0;
          public void increment() {
            x++;
            y++;
          }
       }
      Pair ThreadP;
      public void run() {
        ThreadP.increment();
      }

       // Definition of main method
       public static void main(String args[]) {
          Pair p = new Pair();
          ThreadScheduling3 t1 = new ThreadScheduling3(); 
          ThreadScheduling3 t2 = new ThreadScheduling3();
          t1.ThreadP = p;
          t2.ThreadP = p;
          t1.start();
          t2.start();
          try {
            t1.join();
            t2.join();
          } catch(InterruptedException ie) {};
          System.out.println("x = " +p.x + " ; y = " +p.y);
       }
     }