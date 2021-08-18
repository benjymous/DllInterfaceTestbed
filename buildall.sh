set -e

pushd SolverTests
./build.sh
popd
./bin/SolverTests
pushd Testbed
./build.sh
popd

