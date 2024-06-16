import random
import os
from scipy.spatial import ConvexHull

def generate_worker_data(num_workers):
    names = ["Alice", "Bob", "Charlie", "David", "Eve", "Luke", "Zoe", "Hannah", "Ivy", "Jack",
             "Mia", "Noah", "Liam", "Sophia", "Mason", "Isabella", "James", "Olivia", "Benjamin", "Ava",
             "Elijah", "Emily", "Lucas", "Harper", "Henry", "Amelia", "Alexander", "Ella", "Jackson", "Aiden",
             "Emma", "William", "Oliver", "Sophia", "Charlotte", "Jacob", "Scarlett", "Thomas", "Mia", "Daniel",
             "Gabriel", "Aria", "Samuel", "Grace", "Matthew", "Zoe", "Joseph", "Layla", "Joshua", "Mila",
             "Carter", "Nora", "Wyatt", "Lily", "Sebastian", "Chloe", "Owen", "Hazel", "Dylan", "Ellie",
             "Levi", "Madison", "Isaac", "Luna", "Caleb", "Avery", "Nathan", "Stella", "Hunter", "Hannah",
             "Ryan", "Aurora", "Aaron", "Penelope", "Christian", "Riley", "Landon", "Victoria", "Andrew", "Camila"]
    workers = random.sample(names, num_workers)
    handedness = [random.choice([0, 1]) for _ in range(num_workers)]
    preferences = []

    for worker in workers:
        liked_workers = random.sample([w for w in workers if w != worker], random.randint(1, num_workers-1))
        preferences.append(f"{worker} " + " ".join(liked_workers))

    preferences.append("0")

    return workers, handedness, preferences

def generate_connected_graph(num_points):
    points = [(round(random.uniform(0, 10), 1), round(random.uniform(0, 10), 1)) for _ in range(num_points)]
    start_point_index = random.randint(0, num_points - 1)
    points[start_point_index] = ('*' + str(points[start_point_index][0]), points[start_point_index][1])

    edges = set()
    connected = set()
    remaining = set(range(num_points))

    # Start with the starting point
    connected.add(start_point_index)
    remaining.remove(start_point_index)

    # Identify the convex hull
    hull = ConvexHull([p if isinstance(p[0], float) else (float(p[0][1:]), p[1]) for p in points])
    hull_points = set(hull.vertices)

    # Connect remaining points ensuring the graph is connected
    while remaining:
        from_point = random.choice(list(connected))
        to_point = remaining.pop()
        flow = round(random.uniform(0.1, 10.0), 1)
        edges.add((min(from_point + 1, to_point + 1), max(from_point + 1, to_point + 1), flow))
        connected.add(to_point)

    # Add additional random edges ensuring they are unique and not between border points
    while len(edges) < num_points * 2:
        p1, p2 = random.sample(range(num_points), 2)
        edge = (min(p1 + 1, p2 + 1), max(p1 + 1, p2 + 1))
        if edge not in [(e[0], e[1]) for e in edges] and not (p1 in hull_points and p2 in hull_points):
            flow = round(random.uniform(0.1, 10.0), 1)
            edges.add((edge[0], edge[1], flow))

    return points, edges

def write_worker_file(filename, workers, handedness, preferences):
    with open(filename, 'w') as f:
        f.write(f"{len(workers)}\n")
        for worker, hand in zip(workers, handedness):
            f.write(f"{worker} {hand}\n")
        for preference in preferences:
            f.write(preference + "\n")

def write_points_file(filename, points, edges):
    with open(filename, 'w') as f:
        for point in points:
            f.write(f"{point[0]} {point[1]}\n")
        f.write("\n")
        for edge in edges:
            f.write(f"{edge[0]} {edge[1]} {edge[2]}\n")

def generate_test_case(x):
    base_dir = r'C:\Users\mikol\CLionProjects\plaszczakireal\txt'
    os.makedirs(base_dir, exist_ok=True)

    num_workers = 29
    num_points = 30

    workers, handedness, preferences = generate_worker_data(num_workers)
    points, edges = generate_connected_graph(num_points)

    write_worker_file(os.path.join(base_dir, f'p{x}_w{x}.txt'), workers, handedness, preferences)
    write_points_file(os.path.join(base_dir, f'p{x}_c{x}.txt'), points, edges)

# Generate test cases starting from number 3
for i in range(3, 40):  # Adjust the range to create as many test cases as needed
    generate_test_case(i)
