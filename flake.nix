{
       inputs={
                nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
                flake-parts.url = "github:hercules-ci/flake-parts";
       }; 

        outputs=inputs@{self,nixpkgs,flake-parts}: 
        flake-parts.lib.mkFlake {inherit inputs;} {
                
                systems=["x86_64-linux" "x86_64-darwin" "aarch64-darwin" "aarch64-linux"];
                perSystem= {pkgs, system, ...}:{
                        packages.default=pkgs.stdenv.mkDerivation {
                                name="simplecalculator"; 
                                src=./.;
                                buildPhase="make";
                                installPhase =''
                                        make install PREFIX=$out 
                                '';
                        };
                };
        };
}
