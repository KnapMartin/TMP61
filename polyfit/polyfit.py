import numpy as np
import matplotlib.pyplot as plt
import csv

def fit_thermistor_curve(temperature, resistance):
    # Fit a second-order polynomial (quadratic) to the data
    coefficients = np.polyfit(resistance, temperature, 2)  # Inverting for temperature output
    
    # Generate the polynomial function
    poly_func = np.poly1d(coefficients)
    
    print("Fitted Polynomial Coefficients (ax^2 + bx + c):")
    print(f"a: {coefficients[0]}, b: {coefficients[1]}, c: {coefficients[2]}")
    
    return poly_func

def read_csv(filename):
    temperature = []
    resistance = []
    with open(filename, 'r') as file:
        reader = csv.reader(file)
        for row in reader:
            temperature.append(float(row[0]))
            resistance.append(float(row[1]))
    return np.array(temperature), np.array(resistance)

# Example usage
filename = 'RTtable.csv'  # Update with the actual filename
temp_array, resistance_array = read_csv(filename)

poly_func = fit_thermistor_curve(temp_array, resistance_array)

# Plot the data and the polynomial fit
resistance_range = np.linspace(min(resistance_array), max(resistance_array), 100)
temperature_fit = poly_func(resistance_range)

plt.scatter(resistance_array, temp_array, color='red', label='Data')
plt.plot(resistance_range, temperature_fit, label='2nd Order Fit', color='blue')
plt.xlabel('Resistance (Ω)')
plt.ylabel('Temperature (°C)')
plt.title('Thermistor Temperature vs Resistance')
plt.legend()
plt.grid()
plt.show()
