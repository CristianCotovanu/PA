import java.util.*;

public class Main {

    static class ListNode {
        int val;
        ListNode next;
        ListNode(int x) { val = x; }
    }

    public static void main(String[] args) {
//    	Vector<Complex> v;
//
//        /* Citeste date de test. */
//        v = Complex.readData(".date.in");
//        System.out.println("Vectorul initial:");
//        Complex.writeVector(v);
//
//        /* Verifica sortarea. */
//        Vector<Complex> sorted = getSorted(v);
//        System.out.println("Vectorul sortat:");
//        Complex.writeVector(sorted);
//
//        /* Verifica maparea. */
//        HashMap<Complex,Integer> mapping = getMapping(v);
//        System.out.println("Maparea:");
//        for (Complex element : sorted) {
//        	System.out.println(String.format("%s e pe pozitia %d", element, mapping.get(element)));
//        }
    ListNode list = new ListNode(1);
    ListNode head = list;
    list.next = new ListNode(2);
    list = list.next;
    list.next = new ListNode(3);
    list = list.next;
    list.next = new ListNode(4);
    list = list.next;
    list.next = new ListNode(5);

    printList(head);

    ListNode newHead = swapPairs(head);

    printList(newHead);

    }

    private static void printList(ListNode head) {
        while (head != null) {
            if (head.next == null) {
                System.out.print(head.val);
                break;
            }
            System.out.print(head.val + "->");
            head = head.next;
        }
        System.out.println();
    }

    private static ListNode swapPairs(ListNode head) {
        if (head == null || head.next == null) {
            return head;
        }


        ListNode newHead = head.next;
        ListNode t = head.next;
        ListNode last = head;

        while (t != null && t.next != null) {
            ListNode aux = t.next;


            last = t.next;
            t = t.next.next;
        }

        return newHead;
    }

    private static class ComplexComparator implements Comparator<Complex> {
    	/**
    	 * Functie ce compara doua numere complexe: intai compara partea reala
    	 * si daca ambele numere au aceeasi parte reala, atunci compara partea imaginara 
    	 */
		@Override
		public int compare(Complex a, Complex b) {
			//TODO Intoarceti un numar pozitiv daca a > b, negativ altfel
		    if (a.r > b.r) {
		        return 1;
            } else if (a.r == b.r) {
		        if (a.i > b.i) {
		            return 1;
                } else if (a.i == b.i){
		            return 0;
                } else {
		            return -1;
                }
            } else {
		        return -1;
            }

		}
    }

    /** 
     * Functie ce sorteaza crescator elementele unui vector de numere complexe
     * @param v		vectorul de numere complexe de intrare
     * @return		vectorul de numere complexe sortat descrescator
     */
    private static Vector<Complex> getSorted( Vector<Complex> v ) {
    	Vector<Complex> res = new Vector<Complex>();	// vectorul rezultat
    	
    	/*TODO Folosind PriorityQueue, adaugati elementele din v in ordine crescatoare.
    	 * Pentru PriorityQueue folositi comparatorul definit mai sus */
    	ComplexComparator complexComparator = new ComplexComparator();
        PriorityQueue<Complex> priorityQueue = new PriorityQueue<>(complexComparator);

        priorityQueue.addAll(v);

        for (Complex complex : priorityQueue) {
            res.add(complex);
        }

        return res;
    }
    
    /**
     * Functie ce construieste un HashMap: pentru fiecare element complex atribuie pozitia sa 
     * in vectorul sortat
     * @param v		vectorul de elemente complexe, nesortat
     * @return		HashMap care atribuie pentru fiecare element pozitia sa in vectorul sortat
     */
    private static HashMap<Complex, Integer> getMapping ( Vector<Complex> v) {
    	HashMap<Complex, Integer> res = new HashMap<>();
    	
    	/*TODO Adaugati in map, pentru fiecare element din v, pozitia sa in vectorul sortat. */
        ComplexComparator complexComparator = new ComplexComparator();
        v.sort(complexComparator);

        int pos = 0;
        for (Complex c : v) {
            res.put(c, pos++);
        }
    	
        return res;
    }
    
    
}