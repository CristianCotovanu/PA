import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Main {
    static class Task {
        public final static String INPUT_FILE = "in";
        public final static String OUTPUT_FILE = "out";

        double n;

        private void readInput() {
            try {
                Scanner sc = new Scanner(new File(INPUT_FILE));
                n = sc.nextDouble();
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(double x) {
            try {
                PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE));
                pw.printf("%.4f\n", x);
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private double computeSqrt() {
            double mid = n/2;
            double realValue = Math.sqrt(n);
            double start = 0;
            double end = n;

            while (Math.abs(mid - realValue) > Math.pow(10, -4)) {
                mid = (start + end) / 2;
                double midPow = Math.pow(mid, 2);

                if (midPow > n) {
                    end = mid;
                } else if (midPow < n) {
                    start = mid;
                } else {
                    return mid;
                }
            }
            return mid;
        }

        public void solve() {
            readInput();
            writeOutput(computeSqrt());
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
