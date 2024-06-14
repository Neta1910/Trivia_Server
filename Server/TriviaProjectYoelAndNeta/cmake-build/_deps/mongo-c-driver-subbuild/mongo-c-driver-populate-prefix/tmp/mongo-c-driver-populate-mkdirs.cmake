# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/year2/ekronot/Semester2/trivia4/trivia_neta_orevi_yoel_weisberg_2024/Server/TriviaProjectYoelAndNeta/cmake-build/_deps/mongo-c-driver-src"
  "C:/year2/ekronot/Semester2/trivia4/trivia_neta_orevi_yoel_weisberg_2024/Server/TriviaProjectYoelAndNeta/cmake-build/_deps/mongo-c-driver-build"
  "C:/year2/ekronot/Semester2/trivia4/trivia_neta_orevi_yoel_weisberg_2024/Server/TriviaProjectYoelAndNeta/cmake-build/_deps/mongo-c-driver-subbuild/mongo-c-driver-populate-prefix"
  "C:/year2/ekronot/Semester2/trivia4/trivia_neta_orevi_yoel_weisberg_2024/Server/TriviaProjectYoelAndNeta/cmake-build/_deps/mongo-c-driver-subbuild/mongo-c-driver-populate-prefix/tmp"
  "C:/year2/ekronot/Semester2/trivia4/trivia_neta_orevi_yoel_weisberg_2024/Server/TriviaProjectYoelAndNeta/cmake-build/_deps/mongo-c-driver-subbuild/mongo-c-driver-populate-prefix/src/mongo-c-driver-populate-stamp"
  "C:/year2/ekronot/Semester2/trivia4/trivia_neta_orevi_yoel_weisberg_2024/Server/TriviaProjectYoelAndNeta/cmake-build/_deps/mongo-c-driver-subbuild/mongo-c-driver-populate-prefix/src"
  "C:/year2/ekronot/Semester2/trivia4/trivia_neta_orevi_yoel_weisberg_2024/Server/TriviaProjectYoelAndNeta/cmake-build/_deps/mongo-c-driver-subbuild/mongo-c-driver-populate-prefix/src/mongo-c-driver-populate-stamp"
)

set(configSubDirs Debug)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/year2/ekronot/Semester2/trivia4/trivia_neta_orevi_yoel_weisberg_2024/Server/TriviaProjectYoelAndNeta/cmake-build/_deps/mongo-c-driver-subbuild/mongo-c-driver-populate-prefix/src/mongo-c-driver-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/year2/ekronot/Semester2/trivia4/trivia_neta_orevi_yoel_weisberg_2024/Server/TriviaProjectYoelAndNeta/cmake-build/_deps/mongo-c-driver-subbuild/mongo-c-driver-populate-prefix/src/mongo-c-driver-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
