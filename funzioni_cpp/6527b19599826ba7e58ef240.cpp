write_vector_int(BitWriter& w, int nitems, std::vector<T>& vec,
		 int bits, int_type T::*field)
{
    
    

    for (int i = 0; i < nitems; ++i)
    {
	w.writeBits(vec.at(i).*field, bits);
    }
    
    
    w.flush();
}