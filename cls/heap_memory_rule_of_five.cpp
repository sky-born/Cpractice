#include<iostream>
#include<string>
#include<string_view>
/*
Rule of five
If you wnat to use heap memory of your class,
you need to make 5 operators
~() delete
(&) copy creation
=(&) copy assign
(&&) move creation
=(&&) move assign
Note that move creation and move assign need noexcept command to compatible with standard library.
*/

class SpreadsheetCell
{
private:
  /* data */
  std::string doubleToSting(double inValue) const;
  double stringToDouble(std::string_view inString) const;
  double mValue;
public:
  // creator
  SpreadsheetCell();
  SpreadsheetCell(double initialValue);
  SpreadsheetCell(std::string_view initialValue);
  // copy creator
  SpreadsheetCell(const SpreadsheetCell& src);
  // copy assign
  SpreadsheetCell& operator=(const SpreadsheetCell& rhs);
  // delete
  ~SpreadsheetCell();
  void setValue(double inValue);
  double getValue() const;
  void setString(std::string_view inString);
  std::string getString() const;
};

SpreadsheetCell::SpreadsheetCell(): mValue(0)
{
}

SpreadsheetCell::SpreadsheetCell(double initialValue): mValue(initialValue)
{
}

SpreadsheetCell::SpreadsheetCell(std::string_view initialValue)
{
  setString(initialValue);
}

// copy create
SpreadsheetCell::SpreadsheetCell(const SpreadsheetCell& src): mValue(src.mValue)
{
}

// copy assign
SpreadsheetCell& SpreadsheetCell::operator=(const SpreadsheetCell& rhs)
{
  if(this == &rhs)
  {
    return *this;
  }
  mValue = rhs.mValue;
  return *this;
}

// delete
SpreadsheetCell::~SpreadsheetCell()
{
}

void SpreadsheetCell::setValue(double inValue)
{
  mValue = inValue;
}

double SpreadsheetCell::getValue() const
{
  return mValue;
}

void SpreadsheetCell::setString(std::string_view inString)
{
  mValue = stringToDouble(inString);
}

std::string SpreadsheetCell::getString() const
{
  return doubleToSting(mValue);
}

std::string SpreadsheetCell::doubleToSting(double inValue) const
{
  return std::to_string(inValue);
}

double SpreadsheetCell::stringToDouble(std::string_view inString) const
{
  return std::strtod(inString.data(), nullptr);
}

class Spreadsheet
{
private:
  /* data */
  bool inRange(size_t width, size_t height) const;
  size_t mWidth = 0;
  size_t mHeight = 0;
  SpreadsheetCell** mCells = nullptr;
  void veryfyCoordinate(size_t x, size_t y) const;
  Spreadsheet() = default;
public:
  Spreadsheet(size_t width, size_t height);
  Spreadsheet(const Spreadsheet& src);  // copy create
  Spreadsheet& operator=(const Spreadsheet& rhs);  // copy assign
  friend void swap(Spreadsheet& first, Spreadsheet &second) noexcept;  // for safe memory assign
  Spreadsheet(Spreadsheet&& src) noexcept;  // move create (noexcept required)
  Spreadsheet& operator=(Spreadsheet&& rhs) noexcept;  // move assign (noexcept required)
  ~Spreadsheet();  // delete
  void setCellAt(size_t x, size_t y, const SpreadsheetCell& cell);
  SpreadsheetCell& getCellAt(size_t x, size_t y);
};

Spreadsheet::Spreadsheet(size_t width, size_t height): mWidth(width), mHeight(height)
{
  mCells = new SpreadsheetCell*[mWidth];
  for(size_t i = 0; i < mWidth; i++)
  {
    mCells[i] = new SpreadsheetCell[mHeight];
  }
}

// copy create
Spreadsheet::Spreadsheet(const Spreadsheet& src): Spreadsheet(src.mWidth, src.mHeight)
{
  for(size_t i = 0; i < mWidth; i++)
  {
    for(size_t j = 0; j < mHeight; j++)
    {
      mCells[i][j] = src.mCells[i][j];
    }
  }
}

// // copy assign
// Spreadsheet& Spreadsheet::operator=(const Spreadsheet& rhs)
// {
//   // check if assign itself
//   if (this == &rhs)
//   {
//     return *this;
//   }
//   // delete original memory
//   for (size_t i = 0; i < mWidth; i++)
//   {
//     delete[] = mCells[i];
//   }
//   delete mCells[];
//   mCells = nullptr;
//   // assign new memory
//   mWidth = rhs.mWidth;
//   mHeight = rhs.mHeight;
//   // this may have trouble when memory assign occure exception (not safe) 
//   mCells = new SpreadsheetCell*[mWidth];
//   for(size_t i = 0; i < mWidth; i++)
//   {
//     mCells[i] = new SpreadsheetCell[mHeight];
//   }
//   // copy data
//   for (size_t i = 0; i < mWidth; i++)
//   {
//     for (size_t j = 0; j < mHeight; j++)
//     {
//       mCells[i][j] = rhs.mCells[i][j];
//     }
//   }
//   return *this;
// }

// make swap function for safe copy.
// Note that noexcept command does not keep function from exception, it just guidance of no exception to compiler.
void swap(Spreadsheet& first, Spreadsheet& second) noexcept
{
  using std::swap;
  swap(first.mWidth, second.mWidth);
  swap(first.mHeight, second.mHeight);
  swap(first.mCells, second.mCells); // swap can be done with array
}

// copy assign (safer method)
Spreadsheet& Spreadsheet::operator=(const Spreadsheet& rhs)
{
  // check if assign itself
  if (this == &rhs)
  {
    return *this;
  }

  Spreadsheet temp(rhs); // Do all works in temporary instance.
  swap(*this, temp); // handle data without exception
  return *this;
}


// move creation
Spreadsheet::Spreadsheet(Spreadsheet&& src) noexcept: Spreadsheet()
{
  swap(*this,src);
}

// move assign
Spreadsheet& Spreadsheet::operator=(Spreadsheet&& rhs) noexcept
{
  // check for self assign
  if (this == &rhs)
  {
    return *this;
  }

  Spreadsheet temp(std::move(rhs));
  swap(*this,temp);
  return *this;
}

Spreadsheet::~Spreadsheet()
{
  for(size_t i = 0; i < mWidth; i++)
  {
    delete [] mCells[i];
  }
  delete mCells;
  mCells = nullptr;
  mWidth = 0;
  mHeight = 0;
}

void Spreadsheet::veryfyCoordinate(size_t x, size_t y) const
{
  if(!inRange(x,mWidth) || !inRange(y,mHeight))
  {
    throw std::out_of_range("");
  }
}

void Spreadsheet::setCellAt(size_t x, size_t y, const SpreadsheetCell& cell)
{
  veryfyCoordinate(x, y);
  mCells[x][y] = cell;
}

SpreadsheetCell& Spreadsheet::getCellAt(size_t x, size_t y)
{
  veryfyCoordinate(x, y);
  return mCells[x][y];
}

int main(int argc, char *argv[])
{
    
}