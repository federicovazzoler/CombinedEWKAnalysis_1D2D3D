void convert(double in) {

  ofstream out;
  out.open("out.txt");

  out << in * 1e12;

  out.close();

}
