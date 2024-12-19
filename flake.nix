{
  description = "A Nix-flake development environment for arduino-cli";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
  };

  outputs = { self , nixpkgs ,... }: let
    # system should match the system you are running on
    system = "x86_64-linux";
  in {
    devShells."${system}".default = let
      pkgs = import nixpkgs {
        inherit system;
      };
    in pkgs.mkShell {
      packages = with pkgs; [
        arduino-cli
        python3
        python3Packages.pyserial
      ];

      shellHook = ''
        arduino-cli core install arduino:avr
        arduino-cli lib install Button LiquidCrystal
      '';
    };
  };
}
