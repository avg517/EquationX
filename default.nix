{nixpkgs ? import <nixpkgs>{ } }:
let
        muypkgs=[
                nixpkgs.glfw
                nixpkgs.libGLU
                nixpkgs.glew
                nixpkgs.libgcc
        ];
in
        nixpkgs.stdenv.mkDerivation {
                name="env";
                buildInputs=muypkgs;
        }
