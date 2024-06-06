PM_io_parser(std::ostream& os, const PMDEC& D)
: Base(D), in(std::cin), out(os),
  VI(Base::vertices_begin(),Base::vertices_end(),'v'),
  EI(Base::halfedges_begin(),Base::halfedges_end(),'e'),
  FI(Base::faces_begin(),Base::faces_end(),'f'),
  vn(Base::number_of_vertices()),
  en(Base::number_of_halfedges()),
  fn(Base::number_of_faces())
{ verbose = (get_mode(out) != CGAL::IO::ASCII &&
             get_mode(out) != CGAL::IO::BINARY);
}