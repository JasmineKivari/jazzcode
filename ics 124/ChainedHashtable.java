import java.util.LinkedList;
import java.lang.Math;
import java.util.ListIterator;

public class ChainedHashtable implements LabHashtable {

    private int size;
    private LinkedList[] table;
	
    public Object[] getTable() { 
		return table; 
	}
	
	public ChainedHashtable() {
		table = new LinkedList[100];
		for (int i = 0; i < table.length; i++) {
			table[i] = null;
		}
		size = 0;
	}


	public void put(Object key, Object value) {
		
		int bucket;
		size = getSize();
		
		HashData data = new HashData();
		data.key = key;
		data.value = value;
		
		
		if ((size * 1.25) >= table.length) {
			resize();
		}
		
		bucket = Math.abs(key.hashCode()) % table.length;
		
		if (table[bucket] == null) {
			table[bucket] = new LinkedList <HashData> ();
			table[bucket].add(data);
			size++;

		} else {
			
			ListIterator<HashData> li = table[bucket].listIterator();
			boolean done = false;
			while (!done && li.hasNext()) {
				HashData current = li.next();
				if (current.key.equals(data.key)) {
					current.value = (int) current.value + (int) value;
					
					done = true;
				}
			}		
			if (done == false) {
				table[bucket].add(data);
				size++;
				
			}		
		}	

	}
	
	public Object get(Object key) {
		int bucket;
					
		bucket = Math.abs(key.hashCode()) % table.length;
		
		if (table[bucket] == null) {
			
			return null;			
		} else {
			
			ListIterator<HashData> li = table[bucket].listIterator();
			boolean done = false;
			while (!done && li.hasNext()) {
				HashData current = li.next();
				if (current.key.equals(key)) {
					
					return current.value;
				}
				
			}
					
			return null;			
				
		}
	}
	
	public void resize() {
		LinkedList[] oldTable = table;
		table = new LinkedList[(table.length) * 2];
		for (LinkedList<HashData> item : oldTable) {
			if (item != null) {
				for (HashData data : item) {
					put(data.key, data.value);					
				}
			}
		}
	}	
	
	public int getSize() {
		return size;
	}
    	
}