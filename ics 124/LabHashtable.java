public interface LabHashtable {

    public void put(Object key, Object value);
    public Object get(Object key);
    public int getSize();
    public Object[] getTable();
}