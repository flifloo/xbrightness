# xbrightness
Use xrandr to change brightness when you linux laptop can't use normal way


## Usage
- To shwo current brightnes use `xbrightnes`
    ```
    ❯ xbrightness
    Current: 0.50
    ```

- To set a brightnes use `xbrightnes <level>`, like `0.5` for 50% or `1.0` for 100%
    ```
    ❯ xbrightness 0.5
    Brightness set to 0.50
    ```
    
- To change current brightnes use `xbrightnes <action><level>` action can be `+` or `-`, like `+0.1` or `-0.4`
    ```
    ❯ xbrightness +0.1
    Brightness set to 0.60
    ❯ xbrightness -0.4
    Brightness set to 0.20
    ```


## Installation
- Requerments:
    - Make
    - GCC
    - Xrand

- Commands to install:
    ```
    git clone https://github.com/flifloo/xbrightness.git
    cd xbrightness
    sudo make install
    ```
