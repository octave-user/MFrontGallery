mfront_properties_library(VanadiumAlloy
  VanadiumAlloy_YoungModulus_SRMA
  VanadiumAlloy_PoissonRatio_SRMA
  VanadiumAlloy_ShearModulus_SRMA
  VanadiumAlloy_SpecificHeat_SRMA
  VanadiumAlloy_ThermalExpansion_SRMA
  VanadiumAlloy_ThermalConductivity_SRMA)

# c_property_test(VanadiumAlloy
#   VanadiumAlloy_YoungModulus_SRMA-TestC)
cxx_property_test(VanadiumAlloy
  VanadiumAlloy_YoungModulus_SRMA_TestCxx)
cxx_property_test(VanadiumAlloy
  VanadiumAlloy_ShearModulus_SRMA_TestCxx)
fortran_property_test(VanadiumAlloy
  VanadiumAlloy_YoungModulus_SRMA_TestFortran)
java_property_test(VanadiumAlloy
  VanadiumAlloy_YoungModulus_SRMA_TestJava)
python_property_test(VanadiumAlloy
  VanadiumAlloy_YoungModulus_SRMA_TestPython)
octave_property_test(VanadiumAlloy
  VanadiumAlloy_YoungModulus_SRMA_TestOctave)
octave_property_test(VanadiumAlloy
  VanadiumAlloy_ShearModulus_SRMA_TestOctave)
