# Ramírez Bondi y Martínez Ostoa

# Ejercicio 2

import cv2
import numpy as np
import os
import mahotas as mt
import glob
from sklearn.svm import LinearSVC
from scipy.io import loadmat
from sklearn.neighbors import KNeighborsClassifier
from sklearn.cluster import KMeans

entrena_dir = 'rit18_data.mat'
dataset = loadmat(entrena_dir)
# Datos de entrenamiento
train_data = dataset['train_data']
train_mask = train_data[-1]
train_data = train_data[:6]
train_labels = dataset['train_labels']

# Datos de validación
val_data = dataset['val_data']
val_mask = val_data[-1]
val_data = val_data[:6]
val_labels = dataset['val_labels']

# Datos de prueba
test_data = dataset['test_data']
test_mask = test_data[-1]
test_data = test_data[:6]

band_centers = dataset['band_centers'][0]
band_center_units = dataset['band_center_units']
classes = dataset['classes']


def extraer_caracteristicas(img):
    """Obtener la matriz de Haralick a partir de la matriz proporcionada"""
    print("Extrayendo características...")
    texturas = mt.features.haralick(img)
    return texturas.mean(axis=0)


def muestra_imagen(img, size=(1080, 720)):
    """Llama al método imshow de la biblioteca cv2. Impresión interna de las imágenes con espera de respuesta del usuario."""
    cv2.imshow("Texturas - Reconocimiento de Patrones", cv2.resize(img, size))
    cv2.waitKey(0)


train_data = np.moveaxis(train_data, [2, 0], [0, 2]) # Cambiamos posición de etiqueta de banda al final
test_data = np.moveaxis(test_data, [2, 0], [0, 2])
train_labels = np.moveaxis(train_labels, [1, 0], [0, 1])
val_data = np.moveaxis(val_data, [2, 0], [0, 2])
val_labels = np.moveaxis(val_labels, [1, 0], [0, 1])

print("Transformando imagen a escala de grises...")
grises = train_data[:, :, :3]
grises = cv2.cvtColor(grises, cv2.COLOR_BGR2GRAY)
grises = cv2.resize(grises, (1080, 720))
caracteristicas = extraer_caracteristicas(grises)
print(caracteristicas.shape, grises.shape)
muestra_imagen(grises)

# Modelo

print("Generando modelo...")
svc = LinearSVC(random_state=1618)
print("Entrenando modelo...")
svc.fit(caracteristicas, train_labels)

# Usando KNN

print("Procesando con KNN")
kvecinos = KNeighborsClassifier(n_neighbors=1)
kvecinos.fit(grises.reshape(1, -1), train_labels.reshape(1, -1))
grises_val = val_data[:, :, :3]
grises_val = cv2.cvtColor(grises_val, cv2.COLOR_BGR2GRAY)
print("··· K-Neighbors ···\n", kvecinos.score(grises_val.reshape(1, -1), val_labels.reshape(1, -1)))

# Usando K-Means

print("Procesando con K-Means")
kmedias = KMeans(n_clusters=20, random_state=1618).fit(grises.reshape(1, -1))
print("··· K-Means ···\n", kmedias.score(grises_val.reshape(1, -1)))
