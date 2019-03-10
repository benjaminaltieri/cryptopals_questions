with import <nixpkgs> {};

stdenv.mkDerivation {
  name = "rust-env";
  nativeBuildInputs = [
    # use overlay as described here:
    # https://www.mail-archive.com/nix-dev@lists.science.uu.nl/msg33296.html
    rustChannels.stable.rust

    # Example Build-time Additional Dependencies
    pkgconfig
  ];
  buildInputs = [
    # Example Run-time Additional Dependencies
    #openssl
  ];

  # Set Environment Variables
  RUST_BACKTRACE = 1;
}
