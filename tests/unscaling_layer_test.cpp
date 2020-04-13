//   OpenNN: Open Neural Networks Library
//   www.opennn.net
//
//   U N S C A L I N G   L A Y E R   T E S T   C L A S S                   
//
//   Artificial Intelligence Techniques SL
//   artelnics@artelnics.com

#include "unscaling_layer_test.h"


UnscalingLayerTest::UnscalingLayerTest() : UnitTesting()
{
}


UnscalingLayerTest::~UnscalingLayerTest()
{
}


void UnscalingLayerTest::test_constructor()
{
   cout << "test_constructor\n";

   UnscalingLayer ul1;

   assert_true(ul1.get_type() == Layer::Unscaling, LOG);
   assert_true(ul1.get_descriptives().size() == 0, LOG);

   UnscalingLayer ul2(3);

   assert_true(ul2.get_descriptives().size() == 3, LOG);

   Tensor<Descriptives, 1> descriptives;

   descriptives.resize(2);

   UnscalingLayer ul3(descriptives);

   assert_true(ul3.get_descriptives().size() == 2, LOG);

   UnscalingLayer ul4(ul1);

   assert_true(ul4.get_type() == Layer::Unscaling, LOG);
}

void UnscalingLayerTest::test_destructor()
{
   cout << "test_destructor\n";
}


void UnscalingLayerTest::test_assignment_operator()
{
   cout << "test_assignment_operator\n";

   UnscalingLayer ul_1;
   UnscalingLayer ul_2 = ul_1;

   assert_true(ul_2.get_inputs_number() == 0, LOG);
   assert_true(ul_2.get_neurons_number() == 0, LOG);
}


// GET DIMENSIONS -> (GET_INPUT_VARIABLES_DIM ; GET_OUTPUTS_DIMENSIONS)

void UnscalingLayerTest::test_get_neurons_number()
{
   cout << "test_get_neurons_number\n";

   UnscalingLayer ul1;

   // Test 0

   assert_true(ul1.get_neurons_number() == 0, LOG);
   assert_true(ul1.get_neurons_number() == ul1.get_inputs_number(), LOG);

   // Test 1

   ul1.set(3);

   Tensor<Descriptives, 1> descriptives(3);
   ul1.set_descriptives(descriptives);

   assert_true(ul1.get_neurons_number() == 3, LOG);
   assert_true(ul1.get_neurons_number() == ul1.get_inputs_number(), LOG);
}

void UnscalingLayerTest::test_get_inputs_number()
{
   cout << "test_get_inputs_number\n";

   UnscalingLayer ul1;

   // Test 0

   assert_true(ul1.get_inputs_number() == 0, LOG);
   assert_true(ul1.get_inputs_number() == ul1.get_neurons_number(), LOG);

   // Test 1

   ul1.set(3);

   Tensor<Descriptives, 1> descriptives(3);
   ul1.set_descriptives(descriptives);

   assert_true(ul1.get_inputs_number() == 3, LOG);
   assert_true(ul1.get_inputs_number() == ul1.get_neurons_number(), LOG);
}



void UnscalingLayerTest::test_get_descriptives()
{
   cout << "test_get_descriptives\n";

   // Test 0

   Tensor<Descriptives, 1> descriptives(1);

   UnscalingLayer ul(descriptives);

   Tensor<Descriptives, 1> get_des = ul.get_descriptives();

   assert_true(get_des.dimension(0) == 1, LOG);
   assert_true(abs(get_des(0).minimum + 1) < static_cast<type>(1e-3), LOG);
   assert_true(abs(get_des(0).maximum - 1) < static_cast<type>(1e-3), LOG);
   assert_true(abs(get_des(0).mean - 0) < static_cast<type>(1e-3), LOG);
   assert_true(abs(get_des(0).standard_deviation - 1) < static_cast<type>(1e-3), LOG);

   // Test 1

   Descriptives des_0(1,1,1,0);
   Descriptives des_1(2,2,2,0);

   descriptives.resize(2);
   descriptives.setValues({des_0,des_1});

   ul.set_descriptives(descriptives);

   Tensor<Descriptives, 1> get_des_1 = ul.get_descriptives();

   assert_true(get_des_1.dimension(0) == 2, LOG);
   assert_true(abs(get_des_1(1).minimum - 2) < static_cast<type>(1e-3), LOG);
   assert_true(abs(get_des_1(1).maximum - 2) < static_cast<type>(1e-3), LOG);
   assert_true(abs(get_des_1(1).mean - 2) < static_cast<type>(1e-3), LOG);
   assert_true(abs(get_des_1(1).standard_deviation - 0) < static_cast<type>(1e-3), LOG);
}

void UnscalingLayerTest::test_get_descriptives_matrix()
{
   cout << "test_get_descriptives_matrix\n";

   // Test 0

   Tensor<Descriptives, 1> descriptives(1);

   UnscalingLayer ul(descriptives);

   assert_true(ul.get_descriptives_matrix().size() == 4, LOG);
   assert_true(abs(ul.get_descriptives_matrix()(0,0) + 1) < static_cast<type>(1e-3), LOG);
   assert_true(abs(ul.get_descriptives_matrix()(0,1) - 1) < static_cast<type>(1e-3), LOG);
   assert_true(abs(ul.get_descriptives_matrix()(0,2) - 0) < static_cast<type>(1e-3), LOG);
   assert_true(abs(ul.get_descriptives_matrix()(0,3) - 1) < static_cast<type>(1e-3), LOG);

   // Test 1

   descriptives.resize(2);

   descriptives(0).minimum = 1;
   descriptives(0).maximum = 1;
   descriptives(0).mean = 1;
   descriptives(0).standard_deviation = 0;

   descriptives(1).minimum = 2;
   descriptives(1).maximum = 2;
   descriptives(1).mean = 2;
   descriptives(1).standard_deviation = 0;

   ul.set_descriptives(descriptives);

   assert_true(ul.get_descriptives_matrix().size() == 8, LOG);
   assert_true(abs(ul.get_descriptives_matrix()(0,0) - 1) < static_cast<type>(1e-3), LOG);
   assert_true(abs(ul.get_descriptives_matrix()(0,2) - 1) < static_cast<type>(1e-3), LOG);
   assert_true(abs(ul.get_descriptives_matrix()(1,1) - 2) < static_cast<type>(1e-3), LOG);
   assert_true(abs(ul.get_descriptives_matrix()(1,3) - 0) < static_cast<type>(1e-3), LOG);
}



void UnscalingLayerTest::test_get_minimums()
{
   cout << "test_get_minimums\n";

   UnscalingLayer ul(2);

   // Test 0

   Tensor<Descriptives, 1> descriptives(2);

   ul.set_descriptives(descriptives);

   assert_true(abs(ul.get_minimums()(0) + 1) < static_cast<type>(1e-3), LOG);
   assert_true(abs(ul.get_minimums()(1) + 1) < static_cast<type>(1e-3), LOG);

   // Test 1

   descriptives(0).minimum = 1;
   descriptives(1).minimum = -1;

   ul.set_descriptives(descriptives);

   assert_true(abs(ul.get_minimums()(0) - 1) < static_cast<type>(1e-3), LOG);
   assert_true(abs(ul.get_minimums()(1) + 1) < static_cast<type>(1e-3), LOG);
}

void UnscalingLayerTest::test_get_maximums()
{
   cout << "test_get_maximums\n";

   UnscalingLayer ul(2);

   // Test 0

   Tensor<Descriptives, 1> descriptives(2);

   ul.set_descriptives(descriptives);

   assert_true(abs(ul.get_maximums()(0) - 1) < static_cast<type>(1e-3), LOG);
   assert_true(abs(ul.get_maximums()(1) - 1) < static_cast<type>(1e-3), LOG);

   // Test 1

   descriptives(0).maximum = 1;
   descriptives(1).maximum = -1;

   ul.set_descriptives(descriptives);

   assert_true(abs(ul.get_maximums()(0) - 1) < static_cast<type>(1e-3), LOG);
   assert_true(abs(ul.get_maximums()(1) + 1) < static_cast<type>(1e-3), LOG);
}

/*
void UnscalingLayerTest::test_get_means()
{
   cout << "test_get_means\n";

   UnscalingLayer ul(2);

   // Test 0

   Tensor<Descriptives, 1> descriptives(2);

   ul.set_descriptives(descriptives);

   assert_true(abs(ul.get_means()(0) - 0) < static_cast<type>(1e-3), LOG);
   assert_true(abs(ul.get_means()(1) - 0) < static_cast<type>(1e-3), LOG);

   // Test 1

   descriptives(0).mean = 1;
   descriptives(1).mean = -1;

   sl.set_descriptives(descriptives);

   assert_true(abs(ul.get_means()(0) - 1) < static_cast<type>(1e-3), LOG);
   assert_true(abs(ul.get_means()(1) + 1) < static_cast<type>(1e-3), LOG);
}*/

/*
void UnscalingLayerTest::test_get_standard_deviations()
{
   cout << "test_get_standard_deviations\n";

   UnscalingLayer ul(2);

   // Test 0

   Tensor<Descriptives, 1> descriptives(2);

   ul.set_descriptives(descriptives);

   assert_true(abs(ul.get_standard_deviations()(0) - 1) < static_cast<type>(1e-3), LOG);
   assert_true(abs(ul.get_standard_deviations()(1) - 1) < static_cast<type>(1e-3), LOG);

   // Test 1

   descriptives(0).standard_deviation = 1;
   descriptives(1).standard_deviation = -1;

   ul.set_descriptives(descriptives);

   assert_true(abs(ul.get_standard_deviations()(0) - 1) < static_cast<type>(1e-3), LOG);
   assert_true(abs(ul.get_standard_deviations()(1) + 1) < static_cast<type>(1e-3), LOG);
}*/

/*
void UnscalingLayerTest::test_get_minimum()
{
   cout << "test_get_minimum\n";
}
*/

/*
void UnscalingLayerTest::test_get_maximum()
{
   cout << "test_get_maximum\n";
}
*/

/*
void UnscalingLayerTest::test_get_mean()
{
   cout << "test_get_mean\n";
}*/

/*
void UnscalingLayerTest::test_get_standard_deviation()
{
   cout << "test_get_standard_deviation\n";
}
*/

void UnscalingLayerTest::test_get_unscaling_method()
{
   cout << "test_get_unscaling_method\n";

   UnscalingLayer ul(1);

   // Test

   UnscalingLayer::UnscalingMethod no_unscaling = UnscalingLayer::UnscalingMethod::NoUnscaling;

   UnscalingLayer::UnscalingMethod minimum_maximum = UnscalingLayer::UnscalingMethod::MinimumMaximum;

   UnscalingLayer::UnscalingMethod mean_standard_deviation = UnscalingLayer::UnscalingMethod::MeanStandardDeviation;

   UnscalingLayer::UnscalingMethod logarithmic = UnscalingLayer::UnscalingMethod::Logarithmic;


   ul.set_unscaling_method(no_unscaling);

   assert_true(ul.get_unscaling_method() == UnscalingLayer::UnscalingMethod::NoUnscaling, LOG);
   assert_true(ul.get_unscaling_method() == 0, LOG);

   ul.set_unscaling_method(minimum_maximum);

   assert_true(ul.get_unscaling_method() == UnscalingLayer::UnscalingMethod::MinimumMaximum, LOG);
   assert_true(ul.get_unscaling_method() == 1, LOG);

   ul.set_unscaling_method(mean_standard_deviation);

   assert_true(ul.get_unscaling_method() == UnscalingLayer::UnscalingMethod::MeanStandardDeviation, LOG);
   assert_true(ul.get_unscaling_method() == 2, LOG);

   ul.set_unscaling_method(logarithmic);

   assert_true(ul.get_unscaling_method() == UnscalingLayer::UnscalingMethod::Logarithmic, LOG);
   assert_true(ul.get_unscaling_method() == 3, LOG);
}


void UnscalingLayerTest::test_get_display()
{
   cout << "test_get_display\n";

   UnscalingLayer ul;

   assert_true(ul.get_display(), LOG);
}



void UnscalingLayerTest::test_set()
{
   cout << "test_set\n";

   UnscalingLayer ul;

   // Test 1

   ul.set();

   assert_true(ul.get_descriptives().size() == 0, LOG);

   Tensor<Descriptives, 1> descriptives(4);
   ul.set_descriptives(descriptives);
   ul.set();

   assert_true(ul.get_descriptives().size() == 0, LOG);

   // Test 2

   ul.set();

   Index new_neurons_number(0);
   ul.set(new_neurons_number);

   assert_true(ul.get_descriptives().size()== 0, LOG);

   Index new_inputs_number_ = 4;
   ul.set(new_inputs_number_);

   assert_true(ul.get_descriptives().size()== 4, LOG);
   assert_true(ul.get_inputs_number()== ul.get_descriptives().size(), LOG);

   // Test 3

   ul.set();

   Tensor<Descriptives, 1> descriptives_3;
   ul.set(descriptives_3);

   assert_true(ul.get_descriptives().size()== 0, LOG);

   Tensor<Descriptives, 1> descriptives_3_(4);
   ul.set(descriptives_3_);

   assert_true(ul.get_descriptives().size()== 4, LOG);

   // Test 4

   ul.set();

   UnscalingLayer ul4;
   ul4.set(7);

   ul.set(ul4);

   assert_true(ul.get_descriptives().size() == 7, LOG);
}

void UnscalingLayerTest::test_set_imputs_number()
{
   cout << "test_set_imputs_number\n";

   UnscalingLayer ul;

   Index new_inputs_number;
   ul.set_inputs_number(new_inputs_number);

   assert_true(ul.get_descriptives().size()== 0, LOG);

   Index new_inputs_number_ = 4;
   ul.set_inputs_number(new_inputs_number_);

   assert_true(ul.get_descriptives().size()== 4, LOG);
}

void UnscalingLayerTest::test_set_neurons_number()
{
   cout << "test_set_imputs_number\n";

   UnscalingLayer ul;

   Index new_inputs_number(0);
   ul.set_neurons_number(new_inputs_number);

   assert_true(ul.get_descriptives().size()== 0, LOG);

   Index new_inputs_number_ = 4;
   ul.set_neurons_number(new_inputs_number_);

   assert_true(ul.get_descriptives().size()== 4, LOG);
}

void UnscalingLayerTest::test_set_default()
{
   cout << "test_set_default\n";

   UnscalingLayer ul;

   assert_true( ul.get_type() == Layer::Unscaling, LOG);
   assert_true( ul.get_type() == 7, LOG);
}



void UnscalingLayerTest::test_set_descriptives()
{
   cout << "test_set_descriptives\n";

   UnscalingLayer ul;

   // Test 0

   Tensor<Descriptives, 1> descriptives(1);

   ul.set_descriptives(descriptives);

   assert_true(abs(ul.get_descriptives_matrix()(0,0) + 1) < static_cast<type>(1e-3), LOG);
   assert_true(abs(ul.get_descriptives_matrix()(0,1) - 1) < static_cast<type>(1e-3), LOG);
   assert_true(abs(ul.get_descriptives_matrix()(0,2) - 0) < static_cast<type>(1e-3), LOG);
   assert_true(abs(ul.get_descriptives_matrix()(0,3) - 1) < static_cast<type>(1e-3), LOG);

   // Test 1

   Descriptives des_0(1,1,1,0);
   Descriptives des_1(2,2,2,0);

   descriptives.resize(2);
   descriptives.setValues({des_0,des_1});

   ul.set_descriptives(descriptives);

   assert_true(abs(ul.get_descriptives_matrix()(0,0) - 1) < static_cast<type>(1e-3), LOG);
   assert_true(abs(ul.get_descriptives_matrix()(0,2) - 1) < static_cast<type>(1e-3), LOG);
   assert_true(abs(ul.get_descriptives_matrix()(1,1) - 2) < static_cast<type>(1e-3), LOG);
   assert_true(abs(ul.get_descriptives_matrix()(1,3) - 0) < static_cast<type>(1e-3), LOG);
}

void UnscalingLayerTest::test_set_descriptives_eigen()
{
   cout << "test_set_descriptives_eigen\n";

   UnscalingLayer ul(1);

   // Test 0

   Tensor<type, 2> descriptives_eigen(1,4);

   ul.set_descriptives_eigen(descriptives_eigen);
/*
   assert_true(abs(ul.get_descriptives_matrix()(0,0) + 1) < static_cast<type>(1e-3), LOG);
   assert_true(abs(ul.get_descriptives_matrix()(0,1) - 1) < static_cast<type>(1e-3), LOG);
   assert_true(abs(ul.get_descriptives_matrix()(0,2) - 0) < static_cast<type>(1e-3), LOG);
   assert_true(abs(ul.get_descriptives_matrix()(0,3) - 1) < static_cast<type>(1e-3), LOG);
*/
   // Test 1

   ScalingLayer sl_(2);

   Tensor<type, 2> descriptives_eigen_(2,4);
   descriptives_eigen_.setValues({{1,1,1,0},{2,2,2,0}});

   sl_.set_descriptives_eigen(descriptives_eigen_);

   assert_true(abs(sl_.get_descriptives_matrix()(0,0) - 1) < static_cast<type>(1e-3), LOG);
   assert_true(abs(sl_.get_descriptives_matrix()(0,2) - 1) < static_cast<type>(1e-3), LOG);
   assert_true(abs(sl_.get_descriptives_matrix()(1,1) - 2) < static_cast<type>(1e-3), LOG);
   assert_true(abs(sl_.get_descriptives_matrix()(1,3) - 0) < static_cast<type>(1e-3), LOG);
}

void UnscalingLayerTest::test_set_item_descriptives()
{
   cout << "test_set_item_descriptives\n";

   UnscalingLayer ul(2);

   // Test

   Descriptives des_0(1,1,1,0);
   Descriptives des_1(2,2,2,0);

   ul.set_item_descriptives(0,des_0);
   ul.set_item_descriptives(1,des_1);

   assert_true(abs(ul.get_descriptives_matrix()(0,0) - 1) < static_cast<type>(1e-3), LOG);
   assert_true(abs(ul.get_descriptives_matrix()(0,2) - 1) < static_cast<type>(1e-3), LOG);
   assert_true(abs(ul.get_descriptives_matrix()(1,1) - 2) < static_cast<type>(1e-3), LOG);
   assert_true(abs(ul.get_descriptives_matrix()(1,3) - 0) < static_cast<type>(1e-3), LOG);
}




void UnscalingLayerTest::test_set_minimum()
{
   cout << "test_set_minimum\n";

   UnscalingLayer ul(2);

   // Test 1

   Tensor<Descriptives, 1> descriptives(2);

   ul.set_descriptives(descriptives);

   ul.set_minimum(0, -5);
   ul.set_minimum(1, -6);

   assert_true(abs(ul.get_descriptives_matrix()(0,0) + 5) < static_cast<type>(1e-3), LOG);
   assert_true(abs(ul.get_descriptives_matrix()(1,0) + 6) < static_cast<type>(1e-3), LOG);
}

void UnscalingLayerTest::test_set_maximum()
{
   cout << "test_set_maximum\n";

   UnscalingLayer ul(2);

   // Test 1

   Tensor<Descriptives, 1> descriptives(2);

   ul.set_descriptives(descriptives);

   ul.set_maximum(0, 5);
   ul.set_maximum(1, 6);

   assert_true(abs(ul.get_descriptives_matrix()(0,1) - 5) < static_cast<type>(1e-3), LOG);
   assert_true(abs(ul.get_descriptives_matrix()(1,1) - 6) < static_cast<type>(1e-3), LOG);
}

void UnscalingLayerTest::test_set_mean()
{
   cout << "test_set_mean\n";

   UnscalingLayer ul(2);

   // Test 1

   Tensor<Descriptives, 1> descriptives(2);

   ul.set_descriptives(descriptives);

   ul.set_mean(0, 5);
   ul.set_mean(1, 6);

   assert_true(abs(ul.get_descriptives_matrix()(0,0)) - 5 < static_cast<type>(1e-3), LOG);
   assert_true(abs(ul.get_descriptives_matrix()(1,0)) - 6 < static_cast<type>(1e-3), LOG);
}

void UnscalingLayerTest::test_set_standard_deviation()
{
   cout << "test_set_standard_deviation\n";

   UnscalingLayer ul(2);

   // Test 1

   Tensor<Descriptives, 1> descriptives(2);

   ul.set_descriptives(descriptives);

   ul.set_standard_deviation(0, 5);
   ul.set_standard_deviation(1, 6);

   assert_true(abs(ul.get_descriptives_matrix()(0,0) - 5) < static_cast<type>(1e-3), LOG);
   assert_true(abs(ul.get_descriptives_matrix()(1,0) - 6) < static_cast<type>(1e-3), LOG);
}

/*
void UnscalingLayerTest::test_set_minimums()
{
   cout << "test_set_minimums\n";
}
*/

/*
void UnscalingLayerTest::test_set_maximums()
{
   cout << "test_set_outputs_maximum\n";
}
*/

/*
void UnscalingLayerTest::test_set_statistics()
{
   cout << "test_set_statistics\n";
}
*/


void UnscalingLayerTest::test_set_unscaling_method()
{
   cout << "test_set_unscaling_method\n";

   UnscalingLayer ul(1);

   // Test 1

   ul.set_unscaling_method(UnscalingLayer::UnscalingMethod::NoUnscaling);
   assert_true(ul.get_unscaling_method() == UnscalingLayer::UnscalingMethod::NoUnscaling, LOG);
   assert_true(ul.get_unscaling_method() == 0, LOG);

   ul.set_unscaling_method(UnscalingLayer::UnscalingMethod::MinimumMaximum);
   assert_true(ul.get_unscaling_method() == UnscalingLayer::UnscalingMethod::MinimumMaximum, LOG);
   assert_true(ul.get_unscaling_method() == 1, LOG);

   ul.set_unscaling_method(UnscalingLayer::UnscalingMethod::MeanStandardDeviation);
   assert_true(ul.get_unscaling_method() == UnscalingLayer::UnscalingMethod::MeanStandardDeviation, LOG);
   assert_true(ul.get_unscaling_method() == 2, LOG);

   ul.set_unscaling_method(UnscalingLayer::UnscalingMethod::Logarithmic);
   assert_true(ul.get_unscaling_method() == UnscalingLayer::UnscalingMethod::Logarithmic, LOG);
   assert_true(ul.get_unscaling_method() == 3, LOG);

   // Test 2

   ul.set_unscaling_method("NoUnscaling");
   assert_true(ul.get_unscaling_method() == UnscalingLayer::UnscalingMethod::NoUnscaling, LOG);
   assert_true(ul.get_unscaling_method() == 0, LOG);

   ul.set_unscaling_method("MinimumMaximum");
   assert_true(ul.get_unscaling_method() == UnscalingLayer::UnscalingMethod::MinimumMaximum, LOG);
   assert_true(ul.get_unscaling_method() == 1, LOG);

   ul.set_unscaling_method("MeanStandardDeviation");
   assert_true(ul.get_unscaling_method() == UnscalingLayer::UnscalingMethod::MeanStandardDeviation, LOG);
   assert_true(ul.get_unscaling_method() == 2, LOG);

   ul.set_unscaling_method("Logarithmic");
   assert_true(ul.get_unscaling_method() == UnscalingLayer::UnscalingMethod::Logarithmic, LOG);
   assert_true(ul.get_unscaling_method() == 3, LOG);
}

void UnscalingLayerTest::test_set_display()
{
   cout << "test_set_display\n";

   bool display_true = true;
   bool display_false = false;

   set_display(display_true);
   assert_true(get_display() == true, LOG);

   set_display(display_false);
   assert_true(get_display() == false, LOG);
}



void UnscalingLayerTest::test_calculate_outputs()
{
   cout << "test_calculate_outputs\n";

   UnscalingLayer unscaling_layer;

   Tensor<type, 2> inputs;

   unscaling_layer.set_display(false);

   // Test 0_0

   unscaling_layer.set(1);
   unscaling_layer.set_unscaling_method(UnscalingLayer::NoUnscaling);

   inputs.resize(1,1);
   Tensor<type, 2> outputs = unscaling_layer.calculate_outputs(inputs);
   assert_true(outputs.dimension(0) == 1, LOG);
   assert_true(outputs.dimension(1) == 1, LOG);
   assert_true(abs(outputs(0) - inputs(0)) < static_cast<type>(1e-3), LOG);

   // Test 0_1

   unscaling_layer.set(3);
   unscaling_layer.set_unscaling_method(UnscalingLayer::NoUnscaling);

   inputs.resize(1,3);
   inputs.setConstant(0);
   outputs = unscaling_layer.calculate_outputs(inputs);

   assert_true(outputs.dimension(0) == 1, LOG);
   assert_true(outputs.dimension(1) == 3, LOG);
   assert_true(abs(outputs(0) - static_cast<type>(0)) < static_cast<type>(1e-3), LOG);
   assert_true(abs(outputs(1) - static_cast<type>(0)) < static_cast<type>(1e-3), LOG);
   assert_true(abs(outputs(2) - static_cast<type>(0)) < static_cast<type>(1e-3), LOG);

   // Test 1_0

   unscaling_layer.set(1);
   unscaling_layer.set_unscaling_method(UnscalingLayer::MinimumMaximum);

   inputs.resize(1,1);
   Tensor<type, 2> outputs_1 = unscaling_layer.calculate_outputs(inputs);
   assert_true(outputs_1.dimension(0) == 1, LOG);
   assert_true(outputs_1.dimension(1) == 1, LOG);
   assert_true(abs(outputs_1(0) - inputs(0)) < static_cast<type>(1e-3), LOG);

   // Test 1_1

   unscaling_layer.set(2);
   unscaling_layer.set_unscaling_method(UnscalingLayer::MinimumMaximum);

   Tensor<type, 2> minimums_maximums(2,4);
   minimums_maximums.setValues({{-1000,1000,0,0},{-100,100,0,0}});

   unscaling_layer.set_descriptives_eigen(minimums_maximums);
   inputs.resize(1,2);
   inputs.setValues({{0.1f,0}});
   outputs_1 = unscaling_layer.calculate_outputs(inputs);

   assert_true(outputs_1.dimension(0) == 1, LOG);
   assert_true(outputs_1.dimension(1) == 2, LOG);
   assert_true(abs(outputs_1(0) - static_cast<type>(100)) < static_cast<type>(1e-3), LOG);
   assert_true(abs(outputs_1(1) - static_cast<type>(0)) < static_cast<type>(1e-3), LOG);

   // Test 2_0

   unscaling_layer.set(1);
   unscaling_layer.set_unscaling_method(UnscalingLayer::MeanStandardDeviation);

   inputs.resize(1,1);
   Tensor<type, 2> outputs_2 = unscaling_layer.calculate_outputs(inputs);
   assert_true(outputs_2.dimension(0) == 1, LOG);
   assert_true(outputs_2.dimension(1) == 1, LOG);
   assert_true(abs(outputs_2(0) - inputs(0)) < static_cast<type>(1e-3), LOG);

   // Test 2_1

   unscaling_layer.set(2);
   unscaling_layer.set_unscaling_method(UnscalingLayer::MeanStandardDeviation);

   Tensor<type, 2> mean_standard_deviation(2,4);
   mean_standard_deviation.setValues({{-1,1,-1,-2},{-1,1,2,3}});

   unscaling_layer.set_descriptives_eigen(mean_standard_deviation);
   inputs.resize(1,2);
   inputs.setValues({{-1,1}});
   outputs_2 = unscaling_layer.calculate_outputs(inputs);

   assert_true(outputs_2.dimension(0) == 1, LOG);
   assert_true(outputs_2.dimension(1) == 2, LOG);
   assert_true(abs(outputs_2(0) - static_cast<type>(1)) < static_cast<type>(1e-3), LOG);
   assert_true(abs(outputs_2(1) - static_cast<type>(5)) < static_cast<type>(1e-3), LOG);

   // Test 3_0

   unscaling_layer.set(1);
   unscaling_layer.set_unscaling_method(UnscalingLayer::Logarithmic);

   inputs.resize(1,1);
   Tensor<type, 2> outputs_3 = unscaling_layer.calculate_outputs(inputs);
   assert_true(outputs_3.dimension(0) == 1, LOG);
   assert_true(outputs_3.dimension(1) == 1, LOG);

   assert_true(abs(outputs_3(0) - inputs(0)) < static_cast<type>(1e-3), LOG);

   // Test 3_1

   unscaling_layer.set(2);
   unscaling_layer.set_unscaling_method(UnscalingLayer::Logarithmic);

   Tensor<type, 2> standard_deviation(2,4);
   standard_deviation.setValues({{-1,1,-1,2},{-1,1,1,4}});

   unscaling_layer.set_descriptives_eigen(standard_deviation);
   inputs.resize(1,2);
   inputs.setConstant(1);
   outputs_3 = unscaling_layer.calculate_outputs(inputs);

   assert_true(outputs_3.dimension(0) == 1, LOG);
   assert_true(outputs_3.dimension(1) == 2, LOG);
   assert_true(abs(outputs_3(0) - static_cast<type>(2.7182)) < static_cast<type>(1e-3), LOG);
   assert_true(abs(outputs_3(1) - static_cast<type>(2.7182)) < static_cast<type>(1e-3), LOG);
}


void UnscalingLayerTest::test_write_expression()
{
   cout << "test_write_expression\n";

   UnscalingLayer ul;

   Tensor<string, 1> inputs_names(1);
   Tensor<string, 1> outputs_names(1);

   string expression;

   // Test 1

   ul.set(1);
   ul.set_unscaling_method(UnscalingLayer::NoUnscaling);
   inputs_names.setValues({"x"});
   outputs_names.setValues({"y"});

   expression = ul.write_expression(inputs_names, outputs_names);

   assert_true(expression.empty() == false, LOG);
   assert_true(expression == "y = x;\n", LOG);

   // Test 2

   ul.set(1);
   ul.set_unscaling_method(UnscalingLayer::MinimumMaximum);

   expression = ul.write_expression(inputs_names, outputs_names);

   assert_true(expression.empty() == false, LOG);
   assert_true(expression == "y = 0.5*(x+1)*(1-(-1))+(-1);\n", LOG);

   // Test 3

   ul.set(1);
   ul.set_unscaling_method(UnscalingLayer::MeanStandardDeviation);

   expression = ul.write_expression(inputs_names, outputs_names);

   assert_true(expression.empty() == false, LOG);
   assert_true(expression == "y = (0)+(1)*x;\n", LOG);

   // Test 4

   ul.set(1);
   ul.set_unscaling_method(UnscalingLayer::Logarithmic);

   expression = ul.write_expression(inputs_names, outputs_names);

   assert_true(expression.empty() == false, LOG);
   assert_true(expression == "y = 0.5*exp(x-1)*(1-(-1))+(-1);\n", LOG);
}



void UnscalingLayerTest::test_to_XML()
{
   cout << "test_to_XML\n";

   UnscalingLayer  ul;

   tinyxml2::XMLDocument* uld;
   
   // Test

   uld = ul.to_XML();

   assert_true(uld != nullptr, LOG);

   delete uld;
}

void UnscalingLayerTest::test_from_XML()
{
   cout << "test_from_XML\n";

   UnscalingLayer  ul;

   tinyxml2::XMLDocument* uld;
   
   // Test

   uld = ul.to_XML();

   ul.from_XML(*uld);
 
   delete uld;
}


void UnscalingLayerTest::run_test_case()
{
   cout << "Running unscaling layer test case...\n";

   // Constructor and destructor methods

   test_constructor();
   test_destructor();

   // Assignment operators methods

   test_assignment_operator();

   // Get methods

   // Unscaling layer architecture

   test_get_inputs_number();
   test_get_neurons_number();

   // Output variables descriptives

   test_get_minimums();
   test_get_maximums();

   /*
   test_get_means();
   test_get_standard_deviations();*/

   /*
   test_get_minimum();
   test_get_maximum();
   test_get_mean();
   test_get_standard_deviation();
*/

   // Variables descriptives

   test_get_descriptives();
   test_get_descriptives_matrix();

   // Display messages

   test_get_display();

   // Set methods

   test_set();
   test_set_imputs_number();
   test_set_neurons_number();
   test_set_default();

   // Output variables descriptives

   test_set_descriptives();
   test_set_descriptives_eigen();
   test_set_item_descriptives();


   test_set_minimum();
   test_set_maximum();

/*   test_set_mean();
   test_set_standard_deviation();*/

   /*
   test_set_minimums();
   test_set_maximums();
   test_set_means();
   test_set_standard_deviations();*/

   // Variables descriptives

//   test_set_statistics();

   // Variables scaling and unscaling

   test_get_unscaling_method();

   // Display messages

   test_set_display();

   // Output methods

   test_calculate_outputs();

   // Expression methods

   test_write_expression();

   // Serialization methods

   test_to_XML();
   test_from_XML();

   cout << "End of unscaling layer test case.\n";
}


// OpenNN: Open Neural Networks Library.
// Copyright (C) 2005-2019 Artificial Intelligence Techniques, SL.
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
