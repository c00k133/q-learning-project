#ifndef Q_LEARNING_MATRIX_HPP
#define Q_LEARNING_MATRIX_HPP


class Matrix {
 public:
  Matrix(unsigned int _rows, unsigned int _columns)
    : rows(_rows), columns(_columns);
  Matrix(std::vector<std::vector<double>> _values) : values(_values);

 private:
  unsigned int rows;
  unsigned int columns;
  std::vector<std::vector<double>> values;
};


#endif //Q_LEARNING_MATRIX_HPP
