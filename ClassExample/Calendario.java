 

/**
 * Classe che contiene tutti i metodi per la consultazione del calendario perpetuo
 * @author Porfirio
 * @version 1.0
 */
public class Calendario {

    /** Variabile statica che indica il numero del mese */
    static int m;

    /**
     * Algoritmo di calcolo del giorno della settimana nel calendario perpetuo.
     *
     * @param d giorno (intero)
     * @param m mese (intero tra 1 e 12)
     * @param a anno (intero)
     * @return il giorno della settimana (in italiano, con iniziale maiuscola, senza accento) se la data esiste, altrimenti restituisce "Errore"
     */
    public static String calend(int d, int m, int a) {
        if (m <= 2) {
            m = m + 12;
            a--;
        }
        ;

        int f1 = a / 4;
        int f2 = a / 100;
        int f3 = a / 400;
        int f4 = (int) (2 * m + (.6 * (m + 1)));
        int f5 = a + d + 1;
        int x  = f1 - f2 + f3 + f4 + f5;
        int k  = x / 7;
        int n  = x - k * 7;

        return convert(n);
    }
	
	
	    public static float calend1(int d, int m) 
		{
        
			return (float)d/(float)(m);
			
		}

    /**
     * Trasforma il giorno della settimana numerico nel giorno della settimana in italiano
     * con iniziale maiuscola e senza accento.
     *
     * @param n numero del giorno della settimana (intero tra 0 e 6; 0 indica Domenica, 1 Lunedi e cosi' via)
     * @return il giorno della settimana (in italiano, con iniziale maiuscola, senza accento) se la data esiste, altrimenti restituisce "Errore"
     */
    public static String convert(int n) {
        if (n == 1) {
            return "Lunedi";
        } else if (n == 2) {
            return "Martedi";
        } else if (n == 3) {
            return "Mercoledi";
        } else if (n == 4) {
            return "Giovedi";
        } else if (n == 5) {
            return "Venerdi";
        } else if (n == 6) {
            return "Sabato";
        } else if (n == 0) {
            return "Domenica";
        } else {
            return "Errore";
        }
    }

    /**
     * Metodo che calcola il giorno della settimana della data inserita, nel caso sia una data esistente nel calendario
     *
     * @param d giorno del mese (intero)
     * @param ms mese dell'anno in italiano con iniziale minuscola
     * @param a anno (intero)
     * @return il giorno della settimana (in italiano, con iniziale maiuscola, senza accento) se la data esiste, altrimenti restituisce "Errore"
     */
    public static String giornoDellaSettimana(int d, String ms, int a) {
        m = 0;

        if (ms.equals("gennaio")) {
            m = 1;
        } else if (ms.equals("febbraio")) {
            m = 2;
        } else if (ms.equals("marzo")) {
            m = 3;
        } else if (ms.equals("aprile")) {
            m = 4;
        } else if (ms.equals("maggio")) {
            m = 5;
        } else if (ms.equals("giugno")) {
            m = 6;
        } else if (ms.equals("luglio")) {
            m = 7;
        } else if (ms.equals("agosto")) {
            m = 8;
        } else if (ms.equals("settembre")) {
            m = 9;
        } else if (ms.equals("ottobre")) {
            m = 10;
        } else if (ms.equals("novembre")) {
            m = 11;
        } else if (ms.equals("dicembre")) {
            m = 12;
        }

        if ((m > 0) && valida(d, m, a)) {
            return calend(d, m, a);
        } else {
            return "Errore";
        }
    }

    /**
     * Metodo main che ci consente una prima prova di tentativo
     *
     * @param args il primo e' il giorno del mese, il secondo il mese in italiano, il terzo l'anno
     * @return giorno della settimana corrispondente alla data richiesta
     */
    public static String main(String[] args) {
        if (args.length == 3) {
            int    giorno   = Integer.parseInt(args[0]);
            String mese     = args[1];
            int    anno     = Integer.parseInt(args[2]);
            String giornoDS = new String(giornoDellaSettimana(giorno, mese, anno));

            System.out.println(giornoDS);

            return giornoDS;
        } else {
            return "";
        }
    }

    /**
     * Funzione che verifica se la data esiste nel calendario
     *
     * @param d giorno del mese (intero)
     * @param m mese dell'anno (intero, compreso tra 1 e 12)
     * @param a anno (intero)
     * @return true, se la data esiste, false altrimenti
     */
    public static boolean valida(final int d, int m, int a) {
        if ((d < 1) || (d > 31) || (m == 0) || (a <= 1582)) {
            return false;
        }

        Boolean bisestile = (a % 4 == 0);

        if (bisestile && (a % 100 == 0) && (a % 400 != 0)) {
            bisestile = false;
        }

        if (((m == 2) && (d > 29)) || ((m == 2) && (d == 29) &&!bisestile)) {
            return false;
        }

        if (((m == 4) || (m == 6) || (m == 9) || (m == 11)) && (d > 30)) {
            return false;
        }

        return true;
    }
}