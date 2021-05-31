using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DroneBehaviour : MonoBehaviour
{
    public int ID;
    public List<GameObject> usedCrossroads;
    public GameObject actualCrossroad;
    public GameObject destination;
    public GameObject goTo;

    GameObject[] games;
    private void Awake()
    {
        actualCrossroad = goTo;
    }
    private void Start()
    {
        GetComponent<Movement>().AddDestinationPoint(goTo.transform.position);
    }

    private void CheckDirections()
    {
        GameObject[] posibilities = actualCrossroad.GetComponent<Neighbours>().neighbours;
        List<GameObject> placeToGo = new List<GameObject>();

        foreach (var way in posibilities)
        {
            bool x = true;

            foreach (var usedCrossroad in usedCrossroads)
                if (usedCrossroad == way)
                    if (usedCrossroads[0] != way)
                        if (usedCrossroads[1] != way)
                            x = false;

            if (x)
                placeToGo.Add(way);
        }

        if (placeToGo.Count > 1)
        {
            GameObject imGoingTo = placeToGo[placeToGo.Count - 1];
            placeToGo.RemoveAt(placeToGo.Count - 1);

            foreach (var direction in placeToGo)
            {
                List<GameObject> qwert = new List<GameObject>();
                foreach (var x in usedCrossroads)
                    qwert.Add(x);
                GetComponentInParent<DroneMaster>().CreateDrone(transform, qwert, actualCrossroad, direction);
            }

            GetComponent<Movement>().AddDestinationPoint(imGoingTo.transform.position);
            usedCrossroads.Add(imGoingTo);
            actualCrossroad = imGoingTo;
            placeToGo.Clear();
        }
        if (placeToGo.Count == 1)
        {
            GameObject imGoingTo = placeToGo[0];
            GetComponent<Movement>().AddDestinationPoint(imGoingTo.transform.position);
            usedCrossroads.Add(imGoingTo);
            actualCrossroad = imGoingTo;
            placeToGo.Clear();
        }
    }

    private void Update()
    {
        if (goTo == null)
        {
            if (destination != null)
            {
                Vector3 pos = transform.position;
                pos.z = 0;


                if (pos == actualCrossroad.transform.position)
                {
                        CheckDirections();
                }

                Vector3 dest = destination.transform.GetChild(0).transform.position;
                if((dest.x - 0.1f < pos.x && dest.x + 0.1f > pos.x) && (dest.y - 0.1f < pos.y && dest.y + 0.1f > pos.y))
                {
                    usedCrossroads.RemoveAt(usedCrossroads.Count - 1);
                    usedCrossroads.Add(destination.transform.GetChild(0).gameObject);
                    GetComponentInParent<DroneMaster>().DeleteDrones(ID);
                }

            }

        }
        else
        {
            GetComponent<Movement>().AddDestinationPoint(goTo.transform.position);
            actualCrossroad = goTo;
            usedCrossroads.Add(goTo);
            goTo = null;
        }
    }

    public List<GameObject> SendRoute()
    {
        return usedCrossroads;
    }

}
