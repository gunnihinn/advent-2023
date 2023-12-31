{
  description = "Advent of code 2023";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let pkgs = import nixpkgs { inherit system; };
      in {
        devShell = pkgs.mkShell.override { stdenv = pkgs.clangStdenv; } rec {
          nativeBuildInputs = with pkgs; [ clang cmake ninja gdb ];
        };
      });
}
