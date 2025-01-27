# UniLog firmware

# Getting Started

Use the following commands to initialize the project:

```bash
# Create a secrets file
cp secrets.example.h secrets.h

# You can now edit the secret variables in the secrets.h file
code secrets.h
```

## Pinouts

Editable in `config.h`.

| Component            | Pin   |
|----------------------|-------|
| OLED SDA / SCL       | I2C   |
| RFID-RF522 SDA       | D5    |
| RFID-RF522 SCK       | SCK   |
| RFID-RF522 MOSI      | MOSI  |
| RFID-RF522 MISO      | MISO  |