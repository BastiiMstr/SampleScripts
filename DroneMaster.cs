using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DroneMaster : MonoBehaviour
{
    public GameObject drone;
    public GameObject destination;
    public GameObject actualPosition;

    private int ID = 0;
    
    public void SetNewDestination(GameObject newDestination)
    {
        destination = newDestination;
        List<GameObject> lista = new List<GameObject>();
        CreateDrone(transform, lista, actualPosition,actualPosition);
    }

    public void CreateDrone(Transform position, List<GameObject> usedCrossroads, GameObject actualCrossroad, GameObject goTo)
    {
        GameObject newDrone = Instantiate(drone,position.position,position.rotation,transform);
        newDrone.GetComponent<DroneBehaviour>().ID = ID;
        newDrone.GetComponent<DroneBehaviour>().destination = destination;
        newDrone.GetComponent<DroneBehaviour>().usedCrossroads = usedCrossroads;
        newDrone.GetComponent<DroneBehaviour>().actualCrossroad = actualCrossroad;
        newDrone.GetComponent<DroneBehaviour>().goTo = goTo;
        ID++;
    }

    public void DeleteDrones(int serialNumber)
    {

        int childs = transform.childCount;
        LaunchTracker(serialNumber);

        for (int i = 0; i < childs; i++)
            Destroy(transform.GetChild(i).gameObject);

        ID = 0;

    }

    private void LaunchTracker(int serialnumber)
    {
        List<GameObject> route = transform.GetChild(serialnumber).GetComponent<DroneBehaviour>().SendRoute();

        foreach (var crossroad in route)
        {
            GetComponent<Movement>().AddDestinationPoint(crossroad.transform.position);
            actualPosition = crossroad;
        }
    }
}
