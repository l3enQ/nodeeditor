#include "AbstractGraphModel.hpp"

namespace QtNodes
{

void AbstractGraphModel::setPortLayout(PortLayout layout)
{
  _portLayout = layout;
}

PortLayout AbstractGraphModel::portLayout() const
{
  return _portLayout;
}

}

// CPP is needed to generate the code for signals.
