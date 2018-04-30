import java.util.ArrayList;

public class Primes {

    private static ArrayList<Integer> primes = new ArrayList<Integer>();

    public static int nextPrime(int number){

        //start it off with the basic primes
        if(primes.size() == 0){
            primes.add(2);
            primes.add(3);
            primes.add(5);
            primes.add(7);
        }

        int idx = primes.size()-1;
        int last = primes.get(idx);

        //check if we already have the prime we are looking for
        if(last > number){
            //go to the correct prime and return it
            boolean high = false;
            boolean low = false;
            int prevIdx = 0;
            int spread = 0;
            //keep finagling the index until we're not high or low
            while((high = primes.get(idx-1) > number) || (low = primes.get(idx) <= number)){
                spread = Math.abs(prevIdx-idx);
                //because we always need to move by at least 1 or we will get stuck
                spread = spread < 2 ? 2: spread;
                prevIdx = idx;
                if(high){
                    idx -= spread/2;
                } else if(low){
                    idx += spread/2;
                }
            };
            return primes.get(idx);
        }

        /*FIND OUR NEXT SERIES OF PRIMES*/

        //just in case 'number' was prime
        number++;

        int newPrime = last;
        //just keep adding primes until we find the right one
        while((last = primes.get(primes.size()-1)) < number){
            //here we find the next number
            newPrime += 2;
            //start with the assumption that we have a prime, then try to disprove that
            boolean isPrime = true;
            idx = 0;
            int comparisonPrime;
            int sqrt = (int) Math.sqrt(newPrime);
            //make sure we haven't gone over the square root limit- also use post-increment so that we use the idx 0
            while((comparisonPrime = primes.get(idx++)) <= sqrt){
                if(newPrime % comparisonPrime == 0){
                    isPrime = false;
                }
            }
            if(isPrime){
                primes.add(newPrime);
            }
        }

        return last;
    }
}