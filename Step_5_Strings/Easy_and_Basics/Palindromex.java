public class Palindromex {
    public static void main(String[] args) {
        String s = "A man12, a plan, a canal : Pa21nama";
        System.out.println(palindromeOpt(s));
    }

    public static boolean checkPalindrome(String s) {
        int i = 0, j = s.length()-1;
        while (i < j) {
            if (s.charAt(i) != s.charAt(j)) {
                return false;
            }
            i++; j--;
        }
        return true;
    }

    public static boolean palindrome(String s) {
        String transform = "";
        for (int i = 0; i < s.length(); i++) {
            char ch = s.charAt(i);
            // if s is uppercase
            if ('A' <= ch && ch <= 'Z') {
                transform += (char) (ch - 'A' + 'a');
            }
            // if s is lowercase
            else if ('a' <= ch && ch <= 'z') {
                transform += ch;
            }
        }

        System.out.println(transform);

        return checkPalindrome(transform);
    }

    public static boolean checkAlNum(char ch) {
        if ( ('A' <= ch && ch <= 'Z') || ('a' <= ch && ch <= 'z') ) return true;
        if ('0' <= ch && ch <= '9') return true;

        return false;
    }

    public static boolean palindromeOpt(String s) {
        int n = s.length();
        int i = 0, j = n-1;
        while (i < j) {
            // char at 'i' must be english alphabet
            while (i < n && checkAlNum(s.charAt(i)) != true ) {
                i++;
            }
            if (i == n) break;

            if (i >= j) break;

            while (j >= 0 && checkAlNum(s.charAt(j)) != true) {
                j--;
            }
            if (j == -1) break;

            char ch1 = s.charAt(i);
            char ch2 = s.charAt(j);
            // toLowerCase
            if ('A' <= ch1 && ch1 <= 'Z') {
                ch1 = (char) (ch1 - 'A' + 'a');
            }
            if ('A' <= ch2 && ch2 <= 'Z') {
                ch2 = (char) (ch2 - 'A' + 'a');
            }

            if (ch1 != ch2) return false;
            i++; j--;
        }
        return true;
    }
}