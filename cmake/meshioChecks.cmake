if (NOT EXISTS "${MeshIO_SOURCE_DIR}/test/googletest")
  message(WARNING "google/googletest is not available. Tests will not built.")
  message(WARNING "Did you miss the --recursive option when cloning?")
  message(WARNING "Run the following commands to correct this:")
  message(WARNING "git submodule update --init --recursive")
endif ()

