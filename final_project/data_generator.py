from faker import Faker
import random
import json

fake = Faker()
categorias = ["Eletrônicos", "Livros", "Moda", "Casa", "Brinquedos", "Alimentos"]

produtos = []
for i in range(1, 100001):  
    produto = {
        "id": i,
        "title": fake.catch_phrase(),
        "price": round(random.uniform(10.0, 1000.0), 2),
        "description": fake.text(max_nb_chars=200),
        "category": random.choice(categorias),
        "rating": {
            "rate": round(random.uniform(1.0, 5.0), 1),
            "count": random.randint(1, 5000)
        }
    }
    produtos.append(produto)

with open("produtos_100k.json", "w", encoding="utf-8") as f:
    json.dump(produtos, f, indent=4, ensure_ascii=False)

print("Arquivo produtos.json gerado com sucesso!")
