import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Main {
    static class Task {
        public final static String INPUT_FILE = "in";
        public final static String OUTPUT_FILE = "out";

        int base;
        int exponent;
        int mod;

        private void readInput() {
            try {
                Scanner sc = new Scanner(new File(INPUT_FILE));
                base = sc.nextInt();
                exponent = sc.nextInt();
                mod = sc.nextInt();
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(long result) {
            try {
                PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE));
                pw.printf("%d\n", result);
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private int fastPow(int base, int exponent, int mod) {
//            long first = (long) Math.pow(base, exponent/2);
//            long second = (long) Math.pow(base, exponent/2);
            long third = exponent % 2 == 1 ? 2 : 1;

            long aux = (long) Math.pow(base, exponent/2);
            aux = (aux % mod) * (aux % mod) % mod;

//            long res = (first  * second * third) % mod;
            return (int) aux;
//            return (int) res;
        }

        public void solve() {
//            readInput();
//            long result = fastPow(base, exponent, mod);
//            writeOutput(result);
            base = 1000000006;
            exponent = 2;
            mod = 1000000007;
            System.out.println(fastPow(base, exponent, mod));
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
