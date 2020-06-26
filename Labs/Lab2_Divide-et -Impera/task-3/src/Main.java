import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Main {
    static class Task {
        public final static String INPUT_FILE = "in";
        public final static String OUTPUT_FILE = "out";

        int n, x, y;

        private void readInput() {
            try {
                Scanner sc = new Scanner(new File(INPUT_FILE));
                n = sc.nextInt();
                x = sc.nextInt();
                y = sc.nextInt();
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(int answer) {
            try {
                PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE));
                pw.printf("%d\n", answer);
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private int getAnswer(int n, int x, int y) {
            if (n == 0) {
                return 1;
            }

            int cadran = 0;

            if (x > Math.pow(2, n -1)) {
                cadran += 2;
                x -= Math.pow(2, n - 1);
            }
            if (y > Math.pow(2, n - 1)) {
                cadran += 1;
                y -= Math.pow(2, n - 1);
            }

            return (int) (cadran * Math.pow(2, n - 1) * Math.pow(2, n - 1) + getAnswer(n - 1, x, y));
        }

        public void solve() {
            readInput();
            writeOutput(getAnswer(n, x, y));
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
