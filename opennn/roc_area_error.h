/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.opennn.net                                                                                             */
/*                                                                                                              */
/*   R O C   A R E A   E R R O R   C L A S S   H E A D E R                                                      */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Artificial Intelligence Techniques SL                                                                      */
/*   robertolopez@artelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __ROCAREAERROR_H__
#define __ROCAREAERROR_H__

// System includes

#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <string>
#include <limits>

// OpenNN includes

#include "error_term.h"
#include "data_set.h"
#include "numerical_integration.h"

// TinyXml includes

#include "tinyxml2.h"

namespace OpenNN
{

/// This class represents the sum squared peformance term functional. 
/// This is used as the error term in data modeling problems, such as function regression, 
/// classification or time series prediction.

class RocAreaError : public ErrorTerm
{

public:

   // DEFAULT CONSTRUCTOR

   explicit RocAreaError();

   // NEURAL NETWORK CONSTRUCTOR
  /// ownership not passed

   explicit RocAreaError(NeuralNetwork*);

   // DATA SET CONSTRUCTOR
  /// ownership not passed

   explicit RocAreaError(DataSet*);

   // GENERAL CONSTRUCTOR
  /// ownership not passed

   explicit RocAreaError(NeuralNetwork*, DataSet*);

   // XML CONSTRUCTOR

   explicit RocAreaError(const tinyxml2::XMLDocument&);

   // COPY CONSTRUCTOR

   RocAreaError(const RocAreaError&);

   // DESTRUCTOR

   virtual ~RocAreaError();

   // METHODS

   // Get methods

   // Set methods

   // Checking methods

   void check() const;

   // loss methods

   double calculate_error() const;

//   double calculate_selection_error() const;

   Vector<double> calculate_output_gradient(const Vector<double>&, const Vector<double>&) const;

   Vector<double> calculate_gradient() const;

//   Matrix<double> calculate_Hessian() const;

//   Matrix<double> calculate_single_hidden_layer_Hessian() const;

   double calculate_error(const Vector<double>&) const;

//   double calculate_loss_combination(const size_t&, const Vector<double>&) const;
//   double calculate_loss_combinations(const size_t&, const Vector<double>&, const size_t&, const Vector<double>&) const;

//   Vector<double> calculate_gradient(const Vector<double>&) const;

//   Matrix<double> calculate_output_Hessian(const Vector<double>&, const Vector<double>&) const;

//   Matrix<double> calculate_Hessian(const Vector<double>&) const;

   // Objective terms methods

//   Vector<double> calculate_terms() const;
//   Vector<double> calculate_terms(const Vector<double>&) const;

//   Matrix<double> calculate_terms_Jacobian() const;

//   ErrorTerm::FirstOrderTerms calculate_first_order_terms() const;

   // Squared errors methods

//   Vector<double> calculate_squared_errors() const;

//   string write_error_term_type() const;

   // Serialization methods

//   tinyxml2::XMLDocument* to_XML() const;
//   void from_XML(const tinyxml2::XMLDocument&);

//   void write_XML(tinyxml2::XMLPrinter&) const;
//   void read_XML(   );
private:

   /// Numerical integration used to calculate the error.

   NumericalIntegration numerical_integration;


};

}

#endif


// OpenNN: Open Neural Networks Library.
// Copyright(C) 2005-2018 Artificial Intelligence Techniques, SL.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
